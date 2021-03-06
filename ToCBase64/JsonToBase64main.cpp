#include <iostream>
#include "windows.h"
#include "CBase64.h"
#include "json.h"
using namespace std;

static int s_select = 0;

void writeTestFile( const char *path, string content )
{
   FILE *file = fopen( path, "wb" );
   if ( !file )
      return;
   int size = content.size();
   fwrite( content.c_str() , 1, size, file );
   fclose( file );
}


void findfile() 
{ 
	WIN32_FIND_DATA fd; 
	HANDLE hFind = FindFirstFile("*.json",&fd); 
	if(hFind!=INVALID_HANDLE_VALUE) 
	{ 
		do 
		{ 
			
			string file = readInputTestFile( fd.cFileName );

			Json::Value root;

			if( 1== s_select)
			{
				if( parseAndSaveValueTree( file, "", root ) )
				{ 
					char AssBuffer[64];
					sprintf( AssBuffer, "文件 %s 格式错误！不给力啊", fd.cFileName );
					MessageBox(NULL,AssBuffer,"",MB_OK);
			
				}
				else
				{
					cout<<fd.cFileName<<"格式没错，你是牛逼策划！"<<endl;
				}
			}
			else
			{
				if( parseAndSaveValueTree( file, "", root ) )
				{ 
					char AssBuffer[64];
					sprintf( AssBuffer, "文件%s已经加过密或json格式错误！", fd.cFileName );
					MessageBox(NULL,AssBuffer,"",MB_OK);
			
				}
				else
				{
					string outStr;
					unsigned char buffer[202400];
					memcpy( buffer, file.c_str(),file.size() );
					CBase64::Encode( buffer, file.size(),  outStr );
					writeTestFile( fd.cFileName, outStr );
					cout<<fd.cFileName<<"加密完成！"<<endl;
				}
			}
			//CBase64::Encode( "dgasdg", 3,  outStr );

		}
		while(FindNextFile(hFind,&fd)); 
		FindClose(hFind); 
	} 
	system("pause");
} 


void main()
{
	//CFileFind fd;
	cout<<"json加密编译工具\n";
	cout<<"按1检查json格式===按2检查和加密";

	int input;
	cin>>input;
	s_select = input;
	findfile();
}