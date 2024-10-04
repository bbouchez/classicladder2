// files_project.h

#ifndef __FILES_PROJECT_H__
#define __FILES_PROJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

void VerifyDirectorySelected( char * TheFileProject, char * NewDir );
void InitTempDir( void );
char LoadProjectFiles( char * FileProject );
//char LoadGeneralParamsOnlyFromProject( char * FileProject );
char SaveProjectFiles( char * FileProject );
char JoinFiles( char * DirAndNameOfProject, char * TmpDirectoryFiles, char CompressedProject );
void AddFileToFilesProjectList( char * FileName );
void FreeFilesProjectList( void );
char SplitFiles( char * DirAndNameOfProject, char * TmpDirectoryFiles );

char RemountFileSystemRW( void );
char RemountFileSystemRO( void );

char CopyFile( const char * SrcFile, const char * DestFile );

#ifdef __cplusplus
}
#endif

#endif
