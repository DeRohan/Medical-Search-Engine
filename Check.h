bool Alphabat(char s)
{
	if(s>='A' && s<='Z')
	{
		return true;
	}
	return false;
}

bool Bracket(char s)
{
	if(s=='[')
	{
		return false;
	}
	return true;
}

bool Causebracket(char s)
{
	if(s==']')
	{
		return false;
	}
	return true;
}


bool Riskbracket(char s,int &count)
{
	if(s=='[')
	{
		count+=1;
	}
	if(s=='[' && count==3)
	{
		return false;
	}
	return true;	
}



bool overview(char s,int &count)
{
	if(s=='[')
	{
		count+=1;
	}
	if(s=='[' && count==4)
	{
		return false;
	}
	return true;	
}


bool treatment(char s,int &count)
{
	if(s=='[')
	{
		count+=1;
	}
	if(s=='[' && count==5)
	{
		return false;
	}
	return true;	
}


bool medication(char s,int &count)
{
	if(s=='[')
	{
		count+=1;
	}
	if(s=='[' && count==6)
	{
		return false;
	}
	return true;	
}


bool medicalRemendies(char s,int &count)
{
	if(s=='[')
	{
		count+=1;
	}
	if(s=='[' && count==7)
	{
		return false;
	}
	return true;	
}


bool INDEX(char a)
{
	if(a=='0' || a=='1' || a=='2' || a=='3' || a=='4' || a=='5' || a=='6' || a=='7' || a=='8' || a=='9')
	{
		return true;
	}
	return false;
}

bool Cost(char a,char b,char c)
{
	if(a=='P' && b=='K' && c=='R')
	{
		return false;
	}
	return true;
	
}