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
	int *count;	//�õ�ͳ������ 
 
    char *opt;	//ѡ���ַ������ԡ�-����ͷ�� 
    opterr = 0;
	//getopt(argc, argv, "c:w:l:");
    
	int optind = 1;
	//�õ�ѡ���ַ��� 
	while(optind<argc){		
		if(argv[optind][0]== '-'){
			opt = argv[optind];
			break;
		}
								
		optind++;
	}
	
	//������������� 		
	if(argc<=2){	//��׼���� 
    		count = getNum(NULL,1); 
    		parse(opt,count);
    } else{
		optind = 1;
		while(optind<argc){
			
			if(argv[optind][0]!= '-'){
				if((fp = fopen(argv[optind], "rb")) == NULL )
				{
		        	printf("�ļ�%s��ʧ��\n",argv[optind]);
		        	exit(0);
		    	}
			    	
			    count = getNum(fp,2);		//�ļ����� 
	    		printf("��ǰ�ļ���%s\n",argv[optind]);
	    		parse(opt,count);
	    		fclose(fp);
			}
			optind++;
			
		}			
	}
    	
     
	return 0; 
} 

//ִ��ͳ�ƹ��̣��õ��ַ����������������� 
int * getNum(FILE *p,int style)
{
	static int num[3]; 
	int c,nl, nw, nc, state;
	state = OUT;
    nl = nw = nc = 0;
    
	//while((c = fgetc(p)) != EOF){
	while(c != EOF){
		if(style==1){		//��׼���� 
			c = getchar(); 
		}else{
			c = fgetc(p);	//�ļ�����
		}
		nc++;			//�ַ��� 
		if(c == '\n')
			nl++;		//���� 
		if(c==' ' || c=='\n' || c=='\t')	 
			state = OUT;
		else if (state == OUT) {
	        state = IN;
	        nw++;     //������ 
	    }
	}

	if(c!='\n')
		nl++;		//�е��ļ����һ�в����ڻ��з� ,���⴦�� 
		
	num[0] = nl;
	num[1] = nw;
	num[2] = nc;
	
	return num;
} 

//����ѡ�����ѡ�� 
void parse(char *opt,int *count)
{
	for(int i=1;i<strlen(opt);i++){
		switch(opt[i])
		{
			case 'w':
				printf("��������%d\n",count[1]); break;
			case 'c': 
	            printf("�ַ��� ��%d\n",count[2]); break;
			case 'l':
	            printf("���� ��%d\n",count[0]);	break;
	        default:
	            printf("�ò���ѡ�����\n");
	    }
    } 
} 
