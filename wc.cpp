// wc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include  <stdio.h> 
#include  <string.h>
#include  <io.h> 
#include  <stdlib.h>
#include  <assert.h>

#define   FALSE  0
#define   TRUE   1
#define   LINEMAXSIZE  500
#define   FILEWAYSIZE  300

int    __GiPaperAllLine = 0;                                                                            /* 统计所有文件中的总代码数  */  
int    __GiAllSpaceLine = 0;                                                                            /* 统计所有文件中的空格行数  */
int    __GiAllNoteLine  = 0;                                                                             /* 统计所有文件中的注释行数  */
int    __GiAllUseLine   = 0;                                                                              /* 统计所有文件中的有效行数  */
int    __GiALLPaper     = 0;                                                                              /* 统计文件夹中的文件总数     */


//** Function name:		SafeCopy

bool SafeCopy( char *s1 , char *s2 , int MAXSIZE )
{
	int ii = 0 ;
	for(ii = 0 ; s2[ii]!= '\0'; ii++){
		if(ii>MAXSIZE){
			return FALSE ;
		}
		s1[ii] = s2[ii];
	}
	return TRUE;
}

//** Function name:		InPut


bool InPut( char *FileName )
{
	
	int ii = 0;                                                                                                     /* 循环变量                          */ 
	for( ii = 0; FileName[ii] != '\0'; ii++ ) {                                                        /* 找到文件名的尾部            */
	                                           
	}										                                                                           /*如果输入的是文件路径      */ 
	if( '.' == FileName[ii-1] || '.' ==  FileName[ii-2] || '.' == FileName[ii-4] ){
		return TRUE;
	} else {                                                                                                        /* 如果输入的是文件夹路径  */	
		FileName[ ii ] = '\\';                                                                                /* 在路径后加上 *.* 字符      */
		FileName[ii+1] = '*' ; 
		FileName[ii+2] = '.' ;
		FileName[ii+3] = '*' ;
		FileName[ii+4] = '\0';
		return FALSE;
	}		
}


//** Function name:		FileOpen



bool FileOpen ( FILE ** p , char * s )                                 
{
	
	FILE *pFfp = NULL;
	if(pFfp = fopen( s , "r" )){                                                                            /* 只读方式打开文件            */
		(*p) = pFfp;	
		return TRUE;
	
	}else if( NULL == pFfp ){                                                                             /* 找不到文件则报错 返回 0  */ 
		printf( "无法到达指定目录，统计失败。\n" );
		return FALSE;	
	}
	return FALSE ;
}


//** Function name:		count

void CountFileLines 
	(		char *s,
            int * iAllLine,
            int *iUseLine,
            int * iSpaceLine,
            int * iNoteLine,
            bool * bNote )
		{

			int     i = 0;           
			int     j = 0 ;
			bool    bNoteLineMark = 0;                                                                        /* /*注释行标记变量          */
			bool    bSpaceLineMark = 0;                                                                      /* 空格行标记变量             */
			bool    bUseLineMark = 0;                                                                          /* 有效行标记变量             */
			bool    bTagNote2 = 0;                                                                               /* // 注释行标记变量         */

			for(i = 0; '\0' != s[i];i++ ){                                                                           /* 扫描字符串                    */

				if( i >= LINEMAXSIZE){                                                                           /* 数组访问保护                 */
					break ;
				}

				if( ' ' == s[i] || '\t' == s[i] ) {                                                                     /* 对空格符不做处理          */
				}

				else if(34 == s[i] && (*bNote) == 0 ){                                                    /* 出现" 处理字符串          */
					i++;
					bUseLineMark = 1 ;
					while(34 != s[i] && '\0' != s[i]){
						if( i >= LINEMAXSIZE ){
			    			break ;
					}

						if(s[i]=='\\'&&s[i+1]==34){
							s[i++]='a';
					}
						else if( s[i]=='\\' &&s[i+1] =='\\' ){
							s[i++]= 'a';                      
					}
					s[i] = 'a';
					i++;
			}
		}
        else if('\'' == s[i] && (*bNote) != 1 )                                                       /* 出现 ' 处理字符串         */
        {
            bUseLineMark = 1 ;
            i++ ;
			while('\'' != s[i] && '\0' != s[i]){
                if( i >= LINEMAXSIZE ) {
			        break;
				}
                if(s[i]=='\\'&&s[i+1]=='\'') {
                    s[i++]='a';
				}
                else if( s[i]=='\\' &&s[i+1] =='\\' ){
                    s[i++]= 'a';
				}
				s[i] = 'a';
				i++;
			}
		}
	    else if( ('/' == s[i] && '*' == s[i+1] )&& bTagNote2 != 1 && ( *bNote != 1 ) ){
            i++;                                                                                                     /* 出现 /*                   */
			bNoteLineMark = 1;
			(*bNote) = 1;
		}
        else if( '/' == s[i] && '/' == s[i+1] &&( *bNote != 1 ) ){                         /* 出现//                    */
 			bNoteLineMark = 1;
			bTagNote2 = 1;
            break ;         
		}
        else if(                                                                                                    /* 统计有效行                */
                   (0 == (*bNote)) &&
                   (0 == bTagNote2) &&
                   (s[i] != '/' || s[i+1] != '/') &&
                   (s[i] != '/' || s[i+1] != '*')
               ){
			bUseLineMark = 1;
		}
        else if('*' == s[i] && '/' == s[i+1]){                                                         /* /*注释结束                */
			if(1 == (*bNote)){
                i++ ;
		        bNoteLineMark = 1;
				(*bNote) = 0;
			}
		}
        else if(1 == (*bNote)){
            bNoteLineMark = 1;
        }
        else {
		}
	}


    bSpaceLineMark = 1;
	for(i = 0; '\0' != s[i]; i++){                                                                           /* 统计空格行                */
		if( i >= LINEMAXSIZE ){
			break;
		}
		if(s[i] != ' '&& s[i] != '\t'){
			bSpaceLineMark = 0;
			break;
		}
	}

    if (1 == bSpaceLineMark){
	 	bUseLineMark = 0;
	}

	(*iAllLine)   +=  1;
	(*iNoteLine)  +=  bNoteLineMark;                                                              /* 累加结果                  */
	(*iSpaceLine) +=  bSpaceLineMark;
	(*iUseLine)   +=  bUseLineMark;
		
}

// Function name:		CountFileInfo


void CountFileInfo (FILE * pFfp)
{
	
	char    ch = 0;                                                                                              /* 读取文件的字符变量        */ 
	char    cTemp[LINEMAXSIZE] = {0};                                                            /* 读取单行字符串的变量     */
	int     ii = 0;                                                                                                 /* 循环变量                         */  
	bool    bTagNote   = 0;	                                                                           /* 标记注释符号的变量        */ 

	int     iAllLine   = 0;                                                                                      /* 统计代码行数的变量        */ 
	int     iSpaceLine = 0;                                                                                  /* 统计空格行数的变量        */ 	
	int     iNoteLine  = 0;                                                                                   /* 统计注释行数的变量        */ 
	int     iUseLine   = 0;                                                                                    /* 统计有效代码行数变量     */

	ch = fgetc(pFfp);
	while(EOF != ch){                                                                                        /* 从文件中读取一行代码     */                                     
		
		for(ii = 0; ii<LINEMAXSIZE ; ii++){
			if( '\n' == ch || EOF == ch ){
				cTemp[ii] = '\0';
				break;
			}
			cTemp[ii] = ch;
			ch = fgetc( pFfp );
		} 
		                                                                                                               /* 对该行代码统计                  */
		CountFileLines( cTemp, &iAllLine, &iUseLine, &iSpaceLine, &iNoteLine, &bTagNote );
		cTemp[0] = '\0';
		ch = fgetc (pFfp);
	}
	printf( "空格行数： %d\n" ,  iSpaceLine );                                                   /* 打印出单个文件的统计信息  */
	printf( "总行数  ： %d\n" ,  iAllLine   );
	printf( "注释行数： %d\n" ,  iNoteLine  );
	printf( "有效行数： %d\n" ,  iUseLine   );
	printf( "注释率  ： %f\n" , (double)iNoteLine/(double)iAllLine*100 );
	printf( "-----------------------------------------------\n" );
 
	__GiAllSpaceLine += iSpaceLine;                                                                /* 对文件统计结果进行累加    */                        
	__GiAllNoteLine += iNoteLine; 
	__GiAllUseLine += iUseLine;
	__GiPaperAllLine += iAllLine;
	__GiALLPaper ++;
	fclose(pFfp);	
} 

//** Function name:		Countfile


void CountFile(FILE * fp, char *s)
{
	if( FileOpen(&fp, s))
	CountFileInfo(fp);
}


//** Function name:		CopyFiles


void CopyFiles(char *s1, char *s2)
{
	                
	int    i = 0;                                                                                                   /* 循环变量                      */  
	int    j = 0;                                                                                                   /* 循环变量                      */ 

	for(i = 0; s1[i] != '*'; i++){
    }

	for(j = 0; s2[j] != '\0'; j++){                                                                         /* 拼接字符串                    */
		s1[i++] = s2[j];                                            
	}
	
	s1[i++] = '\\';
	s1[i++] = '*' ;
	s1[i++] = '.' ;
	s1[i++] = '*' ;
	s1[ i ] = '\0';                                                                                                /* 生成子文件及路径          */
	
}


//** Function name:		ChangeFilesWay 


void ChangeFilesWay(char *s1, char *s2)
{

	char * cp = NULL;                                                                                       /* 标记位置的指针            */
	char   ctemp [FILEWAYSIZE] = {0};                                                              /* 保存文件路径              */
	SafeCopy( ctemp , s2 , FILEWAYSIZE);                                          
	strcat(ctemp, "\\*.*");
	cp = strstr(s1, ctemp);                                         
    * cp    = '*';
    *(cp+1) = '.';
    *(cp+2) = '*';
    *(cp+3) = '\0';                                                                                             /* 生成父文件夹路径          */
    
}

//** Function name:		outputfilesway

void outputfilesway(char *s1, char *s2)
{
	int ii = 0;                                                                                                     /* 循环变量                         */

	for(ii = 0; s1[ii] != '*'; ii++){                                                                        /* 生成单个文件的路径         */
	}

  	s1[ii] = '\0';
	strcat(s1,s2);	
	
}


//** Function name:		CheckFile


int CheckFile (char *cPathName)
{
	
	struct     _finddata_t files;                                                                            /* 保存文件信息的结构体       */ 
	FILE *     fp = NULL;                                                                                    /* 文件指针                           */
 	int        iFile_Handle;                                                                                   /* 遍历文件的标志变量           */
	int        ii = 0;				                                                                               /* 循环变量                           */
	int        ij = 0;                                                                                              /* 循环变量                           */ 
	char       ctemp[FILEWAYSIZE] = {0};                                                           /* 保存用户输入的路径          */
	char       cFilesWay[FILEWAYSIZE] = {0};                                                     /* 保存单个文件的路径           */

	SafeCopy( ctemp , cPathName , FILEWAYSIZE);                                         /* 路径拷贝至Temp字符串     */ 					
	iFile_Handle = _findfirst(ctemp,&files);                                                       /* 遍历文件夹                        */
	if(iFile_Handle==-1)
	{                                                                                                                  /* 遍历失败报错                     */
		printf("无法到达指定目录，统计失败。\n");
 	    return 0;
	}
 	do{                                                                                                              /* 对文件夹中文件分类统计   */ 
	                           
		 if( ((_A_SUBDIR|_A_RDONLY) == files.attrib ||
			  _A_SUBDIR == files.attrib ||
			  files.attrib == (_A_ARCH|_A_SUBDIR) || 
			  files.attrib == (_A_ARCH|_A_SUBDIR|_A_RDONLY)) && 
			  files.name[0] != '.'
		   ){	                                                                                                         /* 如果是文件夹                   */	
			CopyFiles(ctemp, files.name);                                                               /* 生成子文件夹的路径         */ 
			CheckFile(ctemp);                                                                                 /* 递归调用本函数                */      
		}
    	else if( 
			     _A_SUBDIR != files.attrib && 
			     (_A_SUBDIR|_A_RDONLY) != files.attrib && 
				 files.attrib != (_A_ARCH|_A_SUBDIR) && 
				 files.attrib != (_A_ARCH|_A_SUBDIR|_A_RDONLY) && 
				 files.name[0] != '.'
				){
		                                                                                                               /* 如果是文件                        */
			strcpy(cFilesWay, ctemp);                                                                   /* 生成文件的路径                 */ 
			for(ii = 0; cFilesWay[ii] != '\0'; ii++){
				
			}

			if(  ('*' != cFilesWay[ii-1]) && ('.' ==  cFilesWay[ii-2] || '.' == cFilesWay[ii-4])){
				
			}	
			
			else{	
				outputfilesway(cFilesWay, files.name);	
			}
			for(ii = 0; cFilesWay[ii] != '\0'; ii++){
				
			}
			if(     						                                                                           /* 是否为.cpp或.c或.h文件   */ 
 				((cFilesWay[ii-1] == 'c' || cFilesWay[ii-1] == 'C' ) && cFilesWay[ii-2] == '.' )||
			    ( 
				  (cFilesWay[ii-1] == 'p'|| cFilesWay[ii-1] == 'P') &&
				  (cFilesWay[ii-2] == 'p' || cFilesWay[ii-2]=='P')&&
	              (cFilesWay[ii-3] == 'c' || cFilesWay[ii-3] == 'C') && 
				   cFilesWay[ii-4] == '.' 
		        )||
 				((cFilesWay[ii-1] == 'h'||cFilesWay[ii-1] == 'H' ) && cFilesWay[ii-2] == '.')

			  ){
			  	printf( "-----------------------------------------------\n" );						                          
				                                                                                                       /* 若是要统计的文件           */
				printf( "文件路径： %s\n",cFilesWay );                                             /* 对文件进行统计              */
				CountFile( fp, cFilesWay ) ; 
			}
			
		}                                                                                                              /* 若子文件夹遍历完毕         */ 
		if( ( (_A_SUBDIR|_A_RDONLY) == files.attrib||
			_A_SUBDIR == files.attrib ||
			files.attrib == (_A_ARCH|_A_SUBDIR) ||
			files.attrib == (_A_ARCH|_A_SUBDIR|_A_RDONLY) ) && 
			files.name[0] != '.'
		  ){
			ChangeFilesWay ( ctemp , files.name);		                                           /* 将路径改为父文件夹进行统计 */
        }
 	}while(0 == _findnext( iFile_Handle, &files));	 
 	_findclose(iFile_Handle);
 	
	return 1;
}

//** Function name:		main


int main( char * arv[] )
{
	char FilesName[FILEWAYSIZE] = {0};
	
        InPut(FilesName);                                                                                    /* 输入文件路径                */
	    CheckFile(FilesName); 
		printf("\n<<<<<<<<<<<<<<<<<<<<<<<<FileInfo>>>>>>>>>>>>>>>>>>>>>>\n");      
	    printf("总文件数   ：  %d\n",  __GiALLPaper);                                           /* 显示统计结果                */ 
	    printf("总行数     :   %d\n",  __GiPaperAllLine);
	    printf("总有效行数 ：  %d\n",  __GiAllUseLine);
	    printf("总注释行数 ：  %d\n",  __GiAllNoteLine);
	    printf("总空格行数 ：  %d\n",  __GiAllSpaceLine);
	    printf("总注释率   ：  %f\n",  (double)__GiAllNoteLine/(double)__GiPaperAllLine*100 ) ;
	    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>\n");  
	    __GiALLPaper = 0;                                                                                   /* 清零统计结果                */
	    __GiPaperAllLine = 0; 
	    __GiAllUseLine = 0;
	    __GiAllNoteLine = 0;
	    __GiAllSpaceLine = 0;
		system("pause");
	}
//   End File
