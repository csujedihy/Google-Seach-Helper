#pragma  once
#include <map>
#include <string>
using namespace std;
namespace Util{
	void param_in_url(char* url,map<string,string>& mp)
	{
		char* pi;
		int len_url = strlen(url);
		int inp,andcnt=0;
		//Get "?" position
		for(int i=0;i!=len_url;i++)	if(url[i]=='\?')inp = i+1;
		for (int i=inp;i!=len_url;i++)	{if(url[i]=='&')andcnt++;}
		for(int i = inp;i < len_url;i++)
		{
			if(url[i]=='&'){
				for (int j = inp;inp !=i;j++)
				{
					if(url[j]=='='){
						int len_pname = j - inp + 1;
						char* pname = (char*)malloc(sizeof(char)*(len_pname));
						for (int k=0;k < len_pname -1;k++)pname[k] = url[inp + k];
						pname[len_pname-1]='\0';
						char* pvalue = (char*)malloc(sizeof(char)*(i-j));
						for (int k =0;k< i - j - 1;k++)pvalue[k] = url[j+1+k];
						pvalue[i-j-1]='\0';
						mp.insert(pair<string,string>(pname,pvalue));
						free(pname);
						free(pvalue);
						break;
					}
				}
				inp = i+1;
				if((--andcnt)==0){
					for (int j = inp;i!=len_url;j++)
					{
						if(url[j]=='='){
							int len_pname = j - inp + 1;
							char* pname = (char*)malloc(sizeof(char)*(len_pname));
							for (int k=0;k < len_pname -1;k++)pname[k] = url[inp + k];
							pname[len_pname-1]='\0';
							char* pvalue = (char*)malloc(sizeof(char)*(len_url-j));
							for (int k =0;k< len_url - j - 1;k++)pvalue[k] = url[j+1+k];
							pvalue[len_url-j-1]='\0';
							mp.insert(pair<string,string>(pname,pvalue));
							free(pname);
							free(pvalue);
							break;
						}
					}

				}
			}
		}

	}
	short int hexChar2dec(char c) {
		if ( '0'<=c && c<='9' ) {
			return short(c-'0');
		} else if ( 'a'<=c && c<='f' ) {
			return ( short(c-'a') + 10 );
		} else if ( 'A'<=c && c<='F' ) {
			return ( short(c-'A') + 10 );
		} else {
			return -1;
		}
	}
	string deescapeURL(const string &URL) {
		string result = "";
		for ( unsigned int i=0; i<URL.size(); i++ ) {
			char c = URL[i];
			if ( c != '%' ) {
				result += c;
			} else {
				char c1 = URL[++i];
				char c0 = URL[++i];
				int num = 0;
				num += hexChar2dec(c1) * 16 + hexChar2dec(c0);
				result += char(num);
			}
		}
		return result;
	}


}
