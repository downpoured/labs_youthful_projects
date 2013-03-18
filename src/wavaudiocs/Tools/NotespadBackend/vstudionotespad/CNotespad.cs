using System;
using CsWaveAudio;
using System.Collections.Generic;
using System.IO;

public class CNotespad
{
    public static void StreamThroughWave(string strFileName, long length)
    {
        if (!File.Exists(strFileName))
            throw new Exception("File not found.");

        using (FileStream fs = new FileStream(strFileName, FileMode.Open, FileAccess.Read))
        using (BufferedStream bs = new BufferedStream(fs, 32768))
        using (BinaryReader r = new BinaryReader(bs))
        {
            StreamThroughWave(r, length);
        }
    }
    public static void StreamThroughWave(BinaryReader r, long nActualLength)
    {
        string riff = new string(r.ReadChars(4));
        if (!riff.Equals("RIFF"))
            throw new Exception("No 'RIFF' Tag, probably not a valid wav file.");

        uint length = r.ReadUInt32(); // (length of file in bytes) - 8
        if (length != nActualLength - 8)
            Console.WriteLine("Warning: claimed length of file="+length+" and actual="+nActualLength);

        string wave = new string(r.ReadChars(4));
        if (!wave.Equals("WAVE"))
            throw new Exception("No 'WAVE' tag, probably not a valid wav file.");

        string format = new string(r.ReadChars(4)); // assume that fmt tag is first
        if (!format.Equals("fmt "))
            throw new Exception("No 'fmt ' tag");

        uint size = r.ReadUInt32(); // size of fmt header
        if (size != 16)
            throw new Exception("Size of fmt header != 16");

        ushort audioformat = r.ReadUInt16(); // audio format. 1 refers to uncompressed PCM
        Console.WriteLine("Audio format: " + audioformat + " (1 is uncompressed PCM)");

        ushort nChannels = r.ReadUInt16();
        uint nSampleRate = r.ReadUInt32();
        uint byteRate = r.ReadUInt32();
        int blockAlign = r.ReadUInt16();
        ushort nBitsPerSample = r.ReadUInt16();

        Console.WriteLine("Sample rate: " + nSampleRate);
        Console.WriteLine("BitsPerSample: " + nBitsPerSample);
        Console.WriteLine("Channels: " + nChannels);

        while (true)
        {
            // Are we at the end of the file?
            byte[] test = r.ReadBytes(4);
            if (test.Length == 0)
                break;
            else
                r.BaseStream.Seek(-test.Length, SeekOrigin.Current);

            // read the next chunk
            string datatag = new string(r.ReadChars(4));
            uint dataSize = r.ReadUInt32();
            if (dataSize > int.MaxValue) throw new Exception("Data size too large.");
            Console.WriteLine("TYPE:" + datatag + " SIZE:" + dataSize);
            if (datatag == "data")
            {
                long nLengthInSamples = dataSize / (nChannels * (nBitsPerSample/8));
                Console.WriteLine("\t(length in samples " + nLengthInSamples+
                    " length in secs " + (nLengthInSamples / ((double)nSampleRate)));
            }
            if (datatag != "data" && datatag != "LIST")
                Console.WriteLine("warning, datatag is not 'data' or 'LIST'.");
            r.BaseStream.Seek(dataSize, SeekOrigin.Current);
        }
        Console.WriteLine("Looks ok.");
    }
    public static WaveAudio Run()
    {
        string[] args = Environment.GetCommandLineArgs();
        if (args.Length < 2 || args[1]=="/?" || args[1]=="-?")
        {
            Console.WriteLine("Usage: audioanalyze.exe input.wav");
            Console.WriteLine("Reading beyond length of file indicates an incorrect .wav file.");
        }
        else if (!File.Exists(args[1]))
        {
            Console.WriteLine("File doesn't seem to exist.");
        }
        else
        {
            FileInfo fInfo = new FileInfo(args[1]);
            long length = fInfo.Length;
            try
            {
                StreamThroughWave(args[1], length);
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: " + e.Message);
            }
        }
        return null;
    }

}
