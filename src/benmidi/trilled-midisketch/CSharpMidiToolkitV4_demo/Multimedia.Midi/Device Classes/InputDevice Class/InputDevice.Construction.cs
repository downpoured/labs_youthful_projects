#region License

/* Copyright (c) 2006 Leslie Sanford
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

#endregion

#region Contact

/*
 * Leslie Sanford
 * Email: jabberdabber@hotmail.com
 */

#endregion

namespace Multimedia.Midi
{
    public sealed partial class InputDevice : Device
    {
        #region Construction

        /// <summary>
        /// Initializes a new instance of the InputDevice class with the 
        /// specified device ID.
        /// </summary>
        public InputDevice(int deviceID)
        {
            Initialize();

            int result = midiInOpen(ref handle, deviceID, midiInProc, 0, CALLBACK_FUNCTION);

            if(result != DeviceException.MMSYSERR_NOERROR)
            {
                throw new InputDeviceException(result);
            }
        }

        ~InputDevice()
        {
            if(!disposed)
            {
                midiInReset(Handle);
                midiInClose(Handle);
            }
        }

        // Initializes the InputDevice.
        private void Initialize()
        {
            midiInProc = HandleMessage;
            onBufferFinished = OnBufferFinished;
            shortMessageHandler = HandleShortMessage;
            sysExMessageHandler = HandleSysExMessage;
            invalidShortMessageHandler = HandleInvalidShortMessage;
            invalidSysExMessageHandler = HandleInvalidSysExMessage;
        }

        #endregion
    }
}