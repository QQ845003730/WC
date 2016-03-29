// wc.cpp : �������̨Ӧ�ó������ڵ㡣
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

int    __GiPaperAllLine = 0;                                                                            /* ͳ�������ļ��е��ܴ�����  */  
int    __GiAllSpaceLine = 0;                                                                            /* ͳ�������ļ��еĿո�����  */
int    __GiAllNoteLine  = 0;                                                                             /* ͳ�������ļ��е�ע������  */
int    __GiAllUseLine   = 0;                                                                              /* ͳ�������ļ��е���Ч����  */
int    __GiALLPaper     = 0;                                                                              /* ͳ���ļ����е��ļ�����     */


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
	
	int ii = 0;                                                                                                     /* ѭ������                          */ 
	for( ii = 0; FileName[ii] != '\0'; ii++ ) {                                                        /* �ҵ��ļ�����β��            */
	                                           
	}										                                                                           /*�����������ļ�·��      */ 
	if( '.' == FileName[ii-1] || '.' ==  FileName[ii-2] || '.' == FileName[ii-4] ){
		return TRUE;
	} else {                                                                                                        /* �����������ļ���·��  */	
		FileName[ ii ] = '\\';                                                                                /* ��·������� *.* �ַ�      */
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
	if(pFfp = fopen( s , "r" )){                                                                            /* ֻ����ʽ���ļ�            */
		(*p) = pFfp;	
		return TRUE;
	
	}else if( NULL == pFfp ){                                                                             /* �Ҳ����ļ��򱨴� ���� 0  */ 
		printf( "�޷�����ָ��Ŀ¼��ͳ��ʧ�ܡ�\n" );
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
			bool    bNoteLineMark = 0;                                                                        /* /*ע���б�Ǳ���          */
			bool    bSpaceLineMark = 0;                                                                      /* �ո��б�Ǳ���             */
			bool    bUseLineMark = 0;                                                                          /* ��Ч�б�Ǳ���             */
			bool    bTagNote2 = 0;                                                                               /* // ע���б�Ǳ���         */

			for(i = 0; '\0' != s[i];i++ ){                                                                           /* ɨ���ַ���                    */

				if( i >= LINEMAXSIZE){                                                                           /* ������ʱ���                 */
					break ;
				}

				if( ' ' == s[i] || '\t' == s[i] ) {                                                                     /* �Կո����������          */
				}

				else if(34 == s[i] && (*bNote) == 0 ){                                                    /* ����" �����ַ���          */
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
        else if('\'' == s[i] && (*bNote) != 1 )                                                       /* ���� ' �����ַ���         */
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
            i++;                                                                                                     /* ���� /*                   */
			bNoteLineMark = 1;
			(*bNote) = 1;
		}
        else if( '/' == s[i] && '/' == s[i+1] &&( *bNote != 1 ) ){                         /* ����//                    */
 			bNoteLineMark = 1;
			bTagNote2 = 1;
            break ;         
		}
        else if(                                                                                                    /* ͳ����Ч��                */
                   (0 == (*bNote)) &&
                   (0 == bTagNote2) &&
                   (s[i] != '/' || s[i+1] != '/') &&
                   (s[i] != '/' || s[i+1] != '*')
               ){
			bUseLineMark = 1;
		}
        else if('*' == s[i] && '/' == s[i+1]){                                                         /* /*ע�ͽ���                */
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
	for(i = 0; '\0' != s[i]; i++){                                                                           /* ͳ�ƿո���                */
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
	(*iNoteLine)  +=  bNoteLineMark;                                                              /* �ۼӽ��                  */
	(*iSpaceLine) +=  bSpaceLineMark;
	(*iUseLine)   +=  bUseLineMark;
		
}

// Function name:		CountFileInfo


void CountFileInfo (FILE * pFfp)
{
	
	char    ch = 0;                                                                                              /* ��ȡ�ļ����ַ�����        */ 
	char    cTemp[LINEMAXSIZE] = {0};                                                            /* ��ȡ�����ַ����ı���     */
	int     ii = 0;                                                                                                 /* ѭ������                         */  
	bool    bTagNote   = 0;	                                                                           /* ���ע�ͷ��ŵı���        */ 

	int     iAllLine   = 0;                                                                                      /* ͳ�ƴ��������ı���        */ 
	int     iSpaceLine = 0;                                                                                  /* ͳ�ƿո������ı���        */ 	
	int     iNoteLine  = 0;                                                                                   /* ͳ��ע�������ı���        */ 
	int     iUseLine   = 0;                                                                                    /* ͳ����Ч������������     */

	ch = fgetc(pFfp);
	while(EOF != ch){                                                                                        /* ���ļ��ж�ȡһ�д���     */                                     
		
		for(ii = 0; ii<LINEMAXSIZE ; ii++){
			if( '\n' == ch || EOF == ch ){
				cTemp[ii] = '\0';
				break;
			}
			cTemp[ii] = ch;
			ch = fgetc( pFfp );
		} 
		                                                                                                               /* �Ը��д���ͳ��                  */
		CountFileLines( cTemp, &iAllLine, &iUseLine, &iSpaceLine, &iNoteLine, &bTagNote );
		cTemp[0] = '\0';
		ch = fgetc (pFfp);
	}
	printf( "�ո������� %d\n" ,  iSpaceLine );                                                   /* ��ӡ�������ļ���ͳ����Ϣ  */
	printf( "������  �� %d\n" ,  iAllLine   );
	printf( "ע�������� %d\n" ,  iNoteLine  );
	printf( "��Ч������ %d\n" ,  iUseLine   );
	printf( "ע����  �� %f\n" , (double)iNoteLine/(double)iAllLine*100 );
	printf( "-----------------------------------------------\n" );
 
	__GiAllSpaceLine += iSpaceLine;                                                                /* ���ļ�ͳ�ƽ�������ۼ�    */                        
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
	                
	int    i = 0;                                                                                                   /* ѭ������                      */  
	int    j = 0;                                                                                                   /* ѭ������                      */ 

	for(i = 0; s1[i] != '*'; i++){
    }

	for(j = 0; s2[j] != '\0'; j++){                                                                         /* ƴ���ַ���                    */
		s1[i++] = s2[j];                                            
	}
	
	s1[i++] = '\\';
	s1[i++] = '*' ;
	s1[i++] = '.' ;
	s1[i++] = '*' ;
	s1[ i ] = '\0';                                                                                                /* �������ļ���·��          */
	
}


//** Function name:		ChangeFilesWay 


void ChangeFilesWay(char *s1, char *s2)
{

	char * cp = NULL;                                                                                       /* ���λ�õ�ָ��            */
	char   ctemp [FILEWAYSIZE] = {0};                                                              /* �����ļ�·��              */
	SafeCopy( ctemp , s2 , FILEWAYSIZE);                                          
	strcat(ctemp, "\\*.*");
	cp = strstr(s1, ctemp);                                         
    * cp    = '*';
    *(cp+1) = '.';
    *(cp+2) = '*';
    *(cp+3) = '\0';                                                                                             /* ���ɸ��ļ���·��          */
    
}

//** Function name:		outputfilesway

void outputfilesway(char *s1, char *s2)
{
	int ii = 0;                                                                                                     /* ѭ������                         */

	for(ii = 0; s1[ii] != '*'; ii++){                                                                        /* ���ɵ����ļ���·��         */
	}

  	s1[ii] = '\0';
	strcat(s1,s2);	
	
}


//** Function name:		CheckFile


int CheckFile (char *cPathName)
{
	
	struct     _finddata_t files;                                                                            /* �����ļ���Ϣ�Ľṹ��       */ 
	FILE *     fp = NULL;                                                                                    /* �ļ�ָ��                           */
 	int        iFile_Handle;                                                                                   /* �����ļ��ı�־����           */
	int        ii = 0;				                                                                               /* ѭ������                           */
	int        ij = 0;                                                                                              /* ѭ������                           */ 
	char       ctemp[FILEWAYSIZE] = {0};                                                           /* �����û������·��          */
	char       cFilesWay[FILEWAYSIZE] = {0};                                                     /* ���浥���ļ���·��           */

	SafeCopy( ctemp , cPathName , FILEWAYSIZE);                                         /* ·��������Temp�ַ���     */ 					
	iFile_Handle = _findfirst(ctemp,&files);                                                       /* �����ļ���                        */
	if(iFile_Handle==-1)
	{                                                                                                                  /* ����ʧ�ܱ���                     */
		printf("�޷�����ָ��Ŀ¼��ͳ��ʧ�ܡ�\n");
 	    return 0;
	}
 	do{                                                                                                              /* ���ļ������ļ�����ͳ��   */ 
	                           
		 if( ((_A_SUBDIR|_A_RDONLY) == files.attrib ||
			  _A_SUBDIR == files.attrib ||
			  files.attrib == (_A_ARCH|_A_SUBDIR) || 
			  files.attrib == (_A_ARCH|_A_SUBDIR|_A_RDONLY)) && 
			  files.name[0] != '.'
		   ){	                                                                                                         /* ������ļ���                   */	
			CopyFiles(ctemp, files.name);                                                               /* �������ļ��е�·��         */ 
			CheckFile(ctemp);                                                                                 /* �ݹ���ñ�����                */      
		}
    	else if( 
			     _A_SUBDIR != files.attrib && 
			     (_A_SUBDIR|_A_RDONLY) != files.attrib && 
				 files.attrib != (_A_ARCH|_A_SUBDIR) && 
				 files.attrib != (_A_ARCH|_A_SUBDIR|_A_RDONLY) && 
				 files.name[0] != '.'
				){
		                                                                                                               /* ������ļ�                        */
			strcpy(cFilesWay, ctemp);                                                                   /* �����ļ���·��                 */ 
			for(ii = 0; cFilesWay[ii] != '\0'; ii++){
				
			}

			if(  ('*' != cFilesWay[ii-1]) && ('.' ==  cFilesWay[ii-2] || '.' == cFilesWay[ii-4])){
				
			}	
			
			else{	
				outputfilesway(cFilesWay, files.name);	
			}
			for(ii = 0; cFilesWay[ii] != '\0'; ii++){
				
			}
			if(     						                                                                           /* �Ƿ�Ϊ.cpp��.c��.h�ļ�   */ 
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
				                                                                                                       /* ����Ҫͳ�Ƶ��ļ�           */
				printf( "�ļ�·���� %s\n",cFilesWay );                                             /* ���ļ�����ͳ��              */
				CountFile( fp, cFilesWay ) ; 
			}
			
		}                                                                                                              /* �����ļ��б������         */ 
		if( ( (_A_SUBDIR|_A_RDONLY) == files.attrib||
			_A_SUBDIR == files.attrib ||
			files.attrib == (_A_ARCH|_A_SUBDIR) ||
			files.attrib == (_A_ARCH|_A_SUBDIR|_A_RDONLY) ) && 
			files.name[0] != '.'
		  ){
			ChangeFilesWay ( ctemp , files.name);		                                           /* ��·����Ϊ���ļ��н���ͳ�� */
        }
 	}while(0 == _findnext( iFile_Handle, &files));	 
 	_findclose(iFile_Handle);
 	
	return 1;
}

//** Function name:		main


int main( char * arv[] )
{
	char FilesName[FILEWAYSIZE] = {0};
	
        InPut(FilesName);                                                                                    /* �����ļ�·��                */
	    CheckFile(FilesName); 
		printf("\n<<<<<<<<<<<<<<<<<<<<<<<<FileInfo>>>>>>>>>>>>>>>>>>>>>>\n");      
	    printf("���ļ���   ��  %d\n",  __GiALLPaper);                                           /* ��ʾͳ�ƽ��                */ 
	    printf("������     :   %d\n",  __GiPaperAllLine);
	    printf("����Ч���� ��  %d\n",  __GiAllUseLine);
	    printf("��ע������ ��  %d\n",  __GiAllNoteLine);
	    printf("�ܿո����� ��  %d\n",  __GiAllSpaceLine);
	    printf("��ע����   ��  %f\n",  (double)__GiAllNoteLine/(double)__GiPaperAllLine*100 ) ;
	    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>\n");  
	    __GiALLPaper = 0;                                                                                   /* ����ͳ�ƽ��                */
	    __GiPaperAllLine = 0; 
	    __GiAllUseLine = 0;
	    __GiAllNoteLine = 0;
	    __GiAllSpaceLine = 0;
		system("pause");
	}
//   End File
