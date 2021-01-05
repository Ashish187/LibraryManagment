#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <dos.h>

typedef struct Book {
	char name[20];
	char author[20];
	char dept[20];
	char bookid[10];
	int quantity;
	int issued;
}Book;

typedef struct IssuedBook {
	char name[20];
	char USN[20];
	char bookid[10];
	char issueDate[20];
}IssuedBook;




void ViewBooks(){
    Book b;
    FILE *fp;
	fp = fopen("Books","a+");
	if(fp==NULL){
		printf(" \n Error in Opening File\n");
		exit(0);
	}
	else{
        printf(" \n ------------------------------------------------------------------------------------------------\n NAME\t\tBOOK ID\t\tAUTHOR\t\tDEPT\t\tQUANT\t\tISSUED\n ------------------------------------------------------------------------------------------------\n");
		while(fscanf(fp,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
            printf(" %s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
		}
		printf(" ------------------------------------------------------------------------------------------------\n");

	}
	fclose(fp);

}

void AddBooks(){
	Book b;
	printf(" \n\n Enter the name of Book : ");
	scanf("%s",b.name);
    printf(" \n Enter the book Id : ");
	scanf("%s",b.bookid);
	printf(" \n Enter the author Name : ");
	scanf("%s",b.author);
	printf(" \n Enter the department book is related to : ");
	scanf("%s",b.dept);
	printf(" \n Enter the quantity : ");
	scanf("%d",&b.quantity);
	b.issued=0;

	FILE *fp;
	fp=fopen("Books","a");
	if(fp==NULL){
		printf(" \n Error in Opening File. \n");
        return;
    }else{
        fprintf(fp,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
        printf(" \n Book %s has been added successfully.\n",b.name);
        fclose(fp);
        return;
    }
}

void RemoveBooks(){
    Book b;
    char bookid[10];
    char choice;
    int flag=0;
    printf(" \n Enter the book Id : ");
    scanf("%s",bookid);

    FILE *fp,*fp1;
	fp = fopen("Books","r+");
	if(fp==NULL){
		printf(" \n Error in Opening File\n");
		exit(0);
	}
	else{
		while(fscanf(fp,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
            if(strcmp(b.bookid,bookid)==0){
                flag=1;
                break;
            }
		}
	}
    rewind(fp);
	if(flag==0){
            printf(" \n Record Not Found!\n");
    }else{
		    printf(" \n Book Found !!\n");
		    printf(" \n Do you want to Remove the Book with Book ID %s (Y/N) : ",b.bookid);
		    scanf("%c",&choice);
		    scanf("%c",&choice);
		    if(choice == 'Y' || choice == 'y'){
            fp1=fopen("temp","w+");
            if(fp1==NULL){
                printf(" \n Error in Opening File\n");
		        exit(0);
            }else{
                while(fscanf(fp,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
                    if(strcmp(b.bookid,bookid)!=0){
                         fprintf(fp1,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
                    }
                }
            }
            fclose(fp);
            fclose(fp1);
            remove("Books");
            rename("temp","Books");
            printf(" \n Book removed Successfully\n");

		    }else{
                return;
		    }
		}


}
void IssueBooks(){
    Book b;
   	IssuedBook b1;
   	char usn[20];
   	char bookid[10];
   	int flag=0;
   	int max=0;
   	int countissued=0;
   	int count = -1;
	FILE *fp,*fp1,*fp2;
	printf(" \n Enter Book Id : ");
	scanf("%s",bookid);

	fp = fopen("Books","r+");
	if(fp==NULL){
		printf(" \n Error in Opening File\n");
		exit(0);
	}
	else{
        rewind(fp);
		while(fscanf(fp,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
            if(strcmp(bookid,b.bookid)==0){
                    flag=1;
                    break;
            }
		}
		if(flag==1){
            fp2= fopen("temp1","a+");
            rewind(fp);
            while(fscanf(fp,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
            if(strcmp(bookid,b.bookid)==0){
                if(b.quantity > 0){
                fp1=fopen("Issued","a+");
                if(fp1==NULL){
                    printf(" \n Error in Opening File\n");
                    exit(0);
                }else{
                    rewind(fp1);
                    printf(" \n Enter the USN : ");
                    scanf("%s",usn);
                    count=0;
                    while(fscanf(fp1,"%s%s%s%s",b1.name,b1.USN,b1.bookid,b1.issueDate)!=EOF){
                        if(strcmp(usn,b1.USN)==0){
                            count++;
                            if(strcmp(bookid,b1.bookid)==0){
                                countissued++;
                            }
                        }

                    }
                    if(count< 5 && count>=0 ){
                        if(countissued == 0){
                        printf(" \n Enter the Name of Student : ")  ;
                        scanf("%s",b1.name);
                        strcpy(b1.USN,usn);
                        strcpy(b1.bookid,bookid);
                        strcpy(b1.issueDate,"12/12/20");
                        fprintf(fp1,"%s\t%s\t%s\t%s\n",b1.name,b1.USN,b1.bookid,b1.issueDate);
                        fprintf(fp2,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity-1,b.issued+1);
                        printf(" \n Book Issued Successfully!!");
                        }else{
                            printf("\n Student has already Issued this Book.\n");
                            fprintf(fp2,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
                        }



                    }else{
                       printf(" \n You have already issued 5 Books\n.");
                       max=1;
                       break;
                    }

                }
            }else{
                printf(" \n Book %s with book ID %s is not available right now.",b.name,b.bookid);
                break;
                //bug is here
            }
		}else{
            fprintf(fp2,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
		}

	}
    fclose(fp1);
	fclose(fp);
	fclose(fp2);
	if(max==0){
      remove("Books");
      rename("temp1","Books");
	}else{
        remove("temp1");
	}



    }else{
       printf(" \n Book Not Found !!!");
       fclose(fp);
    }

}
}

void ReturnBook(){
    char USN[20];
    IssuedBook b1;
    Book b;
    printf("\n Enter the USN : ");
    scanf("%s",USN);
    char choice;
    char bookid[10];
    int flag=0,flag1=0;
    FILE *fp,*fp1,*fp2,*fp3;
    fp=fopen("Issued","r+");
    printf("\n Enter the Book ID : ");
    scanf("%s",bookid);
    while(fscanf(fp,"%s%s%s%s",b1.name,b1.USN,b1.bookid,b1.issueDate)!=EOF){
                if(strcmp(USN,b1.USN)==0){
                    if(strcmp(bookid,b1.bookid)==0){
                        flag=1;
                        break;
                    }
                }
    }
    if(flag==1){
        printf("\n Enter Y if you want to return : ");
        scanf("%c",&choice);
        scanf("%c",&choice);
        if(choice =='y'|| choice=='Y'){
             fp2=fopen("temp1","w+");
             fp3=fopen("Books","a+");
             fp1=fopen("temp","w+");
             rewind(fp);
             while(fscanf(fp,"%s%s%s%s",b1.name,b1.USN,b1.bookid,b1.issueDate)!=EOF){
                if(strcmp(USN,b1.USN)==0){
                    if(strcmp(bookid,b1.bookid)!=0){
                       fprintf(fp1,"%s\t%s\t%s\t%s\n",b1.name,b1.USN,b1.bookid,b1.issueDate);
                    }

                }else{
                    fprintf(fp1,"%s\t%s\t%s\t%s\n",b1.name,b1.USN,b1.bookid,b1.issueDate);
                }
        }
        fclose(fp);
        fclose(fp1);

        while(fscanf(fp3,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
            if(strcmp(bookid,b.bookid)==0){
                fprintf(fp2,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity+1,b.issued-1);
            }else{
              fprintf(fp2,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
            }
        }
        fclose(fp3);
        fclose(fp2);
        remove("Books");
        rename("temp1","Books");
        remove("Issued");
        rename("temp","Issued");
        printf("\n Successfully Returned Book with BookID %s\n-----------------------------------------------.",bookid);
    }else{
        return;
    }
    }else{
        printf("\n No Book with BookId %s was issued to %s",bookid,USN);
        return;
    }


}

void DisplayRecords(char USN[20]){
	IssuedBook b1;
	Book b;
	int flag=0;
	FILE *fp,*fp1;
	fp = fopen("Issued","r");
	if(fp==NULL){
		printf(" \n Error in Opening File\n");
		exit(0);
	}
	else{
        while(fscanf(fp,"%s%s%s%s",b1.name,b1.USN,b1.bookid,b1.issueDate)!=EOF){
                if(strcmp(USN,b1.USN)==0){
                    flag=1;
                    break;
                }
        }
        if(flag==1){
        printf(" \n Printing the records of Book Issued by Student with USN %s ",USN);
        printf(" \n\n--------------------------------------------------------------------\n BookName\t\tAuthor\t\tBookID\t\tIssueDate\n--------------------------------------------------------------------\n");
        rewind(fp);
        fp1=fopen("Books","r");
		while(fscanf(fp,"%s%s%s%s",b1.name,b1.USN,b1.bookid,b1.issueDate)!=EOF){
                if(strcmp(USN,b1.USN)==0){
                    while(fscanf(fp1,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
                        if(strcmp(b1.bookid,b.bookid)==0){
                           break;
                        }
                    }
                     printf(" %s\t\t%s\t\t%s\t\t%s\n",b.name,b.author,b1.bookid,b1.issueDate);
                }
	    }
	    printf("--------------------------------------------------------------------\n");
	    fclose(fp1);
	    fclose(fp);

	}else{
        printf(" \n No any Record Found !!!\n");
        fclose(fp);
        return;
	 }
}

}



void displayStudentOption(){
    while(1){
    printf(" \n -----------------------------");
	printf(" \n Select from the options \n");
	char USN[20];
	int choice;
	printf(" \n 1.View Record of Issued Book\n 2.View Avaliable Book\n 3.Go Back");
	printf(" \n Enter the Choice : ");
    scanf("%d",&choice);
    printf(" -----------------------------\n");
	switch(choice){

		case 1:printf(" \n Enter USN : ");
		       scanf("%s",USN);
		       printf(" \n Searching Records of Student With USN - %s\n",USN);
		       DisplayRecords(USN);
			break;
		case 2:ViewBooks();

			break;
		case 3:	return;
		default:printf(" \n Invalid Option\n");

	}


	}

}

void displayLibrarianOption(){

	int choice;
    while(1){
    printf(" \n -----------------------------");
	printf(" \n Select from the options \n");
	printf(" \n 1.Add Books\n 2.Remove Book\n 3.Issue Book\n 4.Return Book\n 5.View Book List\n 6.Go Back");
	printf(" \n Enter the Choice : ");
    scanf("%d",&choice);
    printf(" -----------------------------\n");
	switch(choice){

		case 1:AddBooks();
		    	break;
		case 2:RemoveBooks();
			   break;
		case 3:	IssueBooks();
		        break;
		case 4:	ReturnBook();
		        break;
		case 5:ViewBooks();
                break;
		case 6:return;
		default:printf(" \n Invalid Option\n");

	}

	}



}




int main(){
	int choice;
	printf("----------------------------------LIBRARY MANAGMENT--------------------------------\n\n");
	while(1){
	printf("\n Select From the Options \n\n 1.Student\n 2.Librarian\n 3.Exit\n\n");

        printf(" Enter your Choice : ");
	scanf("%d",&choice);

	switch(choice){

		case 1: displayStudentOption();
			break;
		case 2:displayLibrarianOption();
			break;
		case 3: exit(0);
		        break;
		default:printf(" \n Invalid Choice\n\n ");

	}
	}



return 0;
}
