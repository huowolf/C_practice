#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IN   1  /* inside a word */
#define OUT  0  /* outside a word */
int * getNum(FILE *p,int style);
void parse(char *opt,int *count);

int main(int argc,char *argv[])
{
	FILE * fp;
	int *count;	//得到统计数据 
 
    char *opt;	//选项字符串（以‘-’开头） 
    opterr = 0;
	//getopt(argc, argv, "c:w:l:");
    
	int optind = 1;
	//得到选项字符串 
	while(optind<argc){		
		if(argv[optind][0]== '-'){
			opt = argv[optind];
			break;
		}
								
		optind++;
	}
	
	//处理输入操作数 		
	if(argc<=2){	//标准输入 
    		count = getNum(NULL,1); 
    		parse(opt,count);
    } else{
		optind = 1;
		while(optind<argc){
			
			if(argv[optind][0]!= '-'){
				if((fp = fopen(argv[optind], "rb")) == NULL )
				{
		        	printf("文件%s打开失败\n",argv[optind]);
		        	exit(0);
		    	}
			    	
			    count = getNum(fp,2);		//文件输入 
	    		printf("当前文件：%s\n",argv[optind]);
	    		parse(opt,count);
	    		fclose(fp);
			}
			optind++;
			
		}			
	}
    	
     
	return 0; 
} 

//执行统计过程，得到字符数，行数，单词数 
int * getNum(FILE *p,int style)
{
	static int num[3]; 
	int c,nl, nw, nc, state;
	state = OUT;
    nl = nw = nc = 0;
    
	//while((c = fgetc(p)) != EOF){
	while(c != EOF){
		if(style==1){		//标准输入 
			c = getchar(); 
		}else{
			c = fgetc(p);	//文件输入
		}
		nc++;			//字符数 
		if(c == '\n')
			nl++;		//行数 
		if(c==' ' || c=='\n' || c=='\t')	 
			state = OUT;
		else if (state == OUT) {
	        state = IN;
	        nw++;     //单词数 
	    }
	}

	if(c!='\n')
		nl++;		//有的文件最后一行不存在换行符 ,特殊处理 
		
	num[0] = nl;
	num[1] = nw;
	num[2] = nc;
	
	return num;
} 

//分离选项，解析选项 
void parse(char *opt,int *count)
{
	for(int i=1;i<strlen(opt);i++){
		switch(opt[i])
		{
			case 'w':
				printf("单词数：%d\n",count[1]); break;
			case 'c': 
	            printf("字符数 ：%d\n",count[2]); break;
			case 'l':
	            printf("行数 ：%d\n",count[0]);	break;
	        default:
	            printf("该参数选项不存在\n");
	    }
    } 
} 
