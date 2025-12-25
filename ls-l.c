//implement ls -l command

#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string.h>

void ftype_permission(long int);

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		puts("format : ./a.out filename");
		return 0;
	}

	int sum=0,second=16;
	char path[512];
	char *cp;
	
	DIR *dp;
	struct dirent *p;
	struct stat v;
	struct passwd *up;
	struct group *gp;

	dp=opendir(argv[1]);
	if(dp==NULL)
	{
		perror("open");
		return 0;
	}
	
	while(p=readdir(dp))
	{
		if(p->d_name[0]=='.')
			continue;//hiding parent & present working directory informations
		
		sprintf(path,"%s/%s",argv[1],p->d_name);//stat function requires first arg as pathname
		
		if(lstat(path,&v)<0)
			continue;//upon lstat failure case continue the iteration for another file
		
		ftype_permission(v.st_mode);//function to print each file type & permissions
		
		printf("%lu ",v.st_nlink);//printing each file contains no of links
		
		/*printing usr_name & grp_name of each file in a directory*/	
		up=getpwuid(v.st_uid);
		gp=getgrgid(v.st_gid);
		
		printf("%s ",up->pw_name);
		printf("%s ",gp->gr_name);
		/**********************************************************/

		int n=printf("%ld ",v.st_size);//printing size of each file
		for(int i=0;i<6-n;i++)
		putchar(' ');
		
		/*printing modify time of each file in a directory as a timestamp*/
		cp=ctime(&v.st_mtime);
		cp[second]='\0';
		
		printf("%s ",cp+4);
		printf("%s ",p->d_name);
		printf("\n");
		/****************************************************************/
			
		sum=(sum+v.st_blocks);//adding each file allocated blocks

	}//end of while
	
	printf("total %d\n",sum/2);//printing toatl blocks used in a directory
}

void ftype_permission(long int mode)
{
	int i;	
	
	/*verify each file is which type*/
	switch(mode>>9)
	{
		case 64:printf("-");
			break;
		case 32:printf("d");
			break;
		case 48:printf("b");
			break;
		case 16:printf("c");
			break;
		case  8:printf("p");
			break;
		case 80:printf("l");
			break;
		case 96:printf("s");
			break;
		default:printf("0");
	}
	/******************************/

	/*printing the permissions of each file*/
	for(i=6;i>=0;i-=3)
	{
		if((mode>>i&7)==0)
			printf("---");
		else if((mode>>i&6)==0)
			printf("--x");
		else if((mode>>i&5)==0)
			printf("-w-");
		else if((mode>>i&4)==0)
			printf("-wx");
		else if((mode>>i&3)==0)
			printf("r--");
		else if((mode>>i&2)==0)
			printf("r-x");
		else if((mode>>i&1)==0)
			printf("rw-");
		else
			printf("rwx");
	}
		printf(" ");
	/**************************************/
}


