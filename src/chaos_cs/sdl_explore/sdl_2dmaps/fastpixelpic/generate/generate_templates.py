
import re
import os


	
def writeTemplates(s, PathToSln):
	#split into 3 parts.
	assert '\n//$$standardloop' in s
	assert '\n//$$endstandardloop' in s
	
	sp1 = s.split('\n//$$standardloop')
	assert len(sp1)==2
	codeBefore = sp1[0]
	codeInside, codeNothingAfterwards = sp1[1].split('\n//$$endstandardloop')
	if codeNothingAfterwards.strip()!='':
		print 'Warning: Ignored code outside of //$$standardloop'
	
	assert codeInside.strip()!=''
	
	# put the blank OnSetup in if it doesn't exist.
	if not re.search(r'\bOnSetup\b',codeBefore):
		codeBefore = 'void OnSetup(int width) { }\n\n'+codeBefore
	
	#read in template.
	projpath=  os.path.join(PathToSln, 'fastpixelpic')
	strTemplate = open(os.path.join(projpath, 'user_code-template.h'),'r').read()
	strTemplate = strTemplate.replace('//$$INSERT_USER_OUTSIDE',codeBefore)
	strTemplate = strTemplate.replace('//$$INSERT_USER_INSIDE',codeInside)
	
	#write the template
	fout=open(os.path.join(projpath, 'user_code.h'),'w')
	fout.write(strTemplate)
	fout.close()
	return True

