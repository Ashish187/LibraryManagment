#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

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
	int bookid;
	char issueDate[20];
}IssuedBook;


void ViewBooks(){
    Book b;

    FILE *fp;
	fp = fopen("Books","r");
	if(fp==NULL){
		printf("\nError in Opening File\n");
		exit(0);
	}
	else{
        printf("\nNAME\t\tBOOK ID\t\tAUTHOR\t\tDEPT\t\tQUANT\t\tISSUED\n------------------------------------------------------------------------------------------------\n");
		while(fscanf(fp,"%s%s%s%s%d%d",b.name,b.bookid,b.author,b.dept,&b.quantity,&b.issued)!=EOF){
            printf("%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
		}
		printf("------------------------------------------------------------------------------------------------\n");

	}
	fclose(fp);

}

void AddBooks(){
    system("clear");
	Book b;
	printf("\n\nEnter the name of Book : ");
	scanf("%s",b.name);
    printf("\nEnter the book Id : ");
	scanf("%s",b.bookid);
	printf("\nEnter the author Name : ");
	scanf("%s",b.author);
	printf("\nEnter the department book is related to : ");
	scanf("%s",b.dept);
	printf("\nEnter the quantity : ");
	scanf("%d",&b.quantity);
	b.issued=0;

	FILE *fp;
	fp=fopen("Books","a");
	if(fp==NULL){
		printf("\nError in Opening File. \n");
        return;
    }else{
        fprintf(fp,"%s\t%s\t%s\t%s\t%d\t%d\n",b.name,b.bookid,b.author,b.dept,b.quantity,b.issued);
        printf("\nBook %s has been added successfully.\n",b.name);
        fclose(fp);

        return;
    }
}

void RemoveBooks(){
    Book b;
    char bookid[10];
    char choice;
    int flag=0;
    printf("\nEnter the book Id : ");
    scanf("%s",bookid);

    FILE *fp,*fp1;
	fp = fopen("Books","r+");
	if(fp==NULL){
		printf("\nError in Opening File\n");
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
            printf("\nRecord Not Found!\n");
    }else{
		    printf("\nBook Found !!\n");
		    printf("\nDo you want to Remove the Book with Book ID %s (Y/N) : ",b.bookid);
		    scanf("%c",&choice);
		    scanf("%c",&choice);
		    if(choice == 'Y' || choice == 'y'){
            fp1=fopen("temp","w");
            if(fp1==NULL){
                printf("\nError in Opening File\n");
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
            printf("\nBook removed Successfully\n");

		    }else{
                return;
		    }
		}


}
void IssueBooks(){

}

void DisplayRecords(char USN[20]){
	IssuedBook b;
	FILE *fp;
	fp = fopen("Issued","r");
	if(fp==NULL){
		printf("\nError in Opening File\n");
		exit(0);
	}
	else{

		while(fscanf(fp,"%s%s%d%s",b.name,b.USN,&b.bookid,b.issueDate)!=EOF){

		}
	}
	fclose(fp);

}



void displayStudentOption(){
    while(1){
	printf("\nSelect from the options \n");
	char USN[20];
	int choice;
	printf("\n1.View Record of Issued Book\n2.View Avaliable Book\n3.Go Back");
	printf("\nEnter the Choice : ");
        scanf("%d",&choice);
	switch(choice){

		case 1:printf("\nEnter USN : ");
		       scanf("%s",USN);
		       printf("\nShowing Records of Student With USN - %s\n\n",USN);
		       DisplayRecords(USN);
			break;
		case 2:ViewBooks();

			break;
		case 3:	return;
		default:printf("\nInvalid Option\n");

	}


	}

}

void displayLibrarianOption(){
	int choice;
    while(1){
	printf("\nSelect from the options \n");
	printf("\n1.Add Books\n2.Remove Book\n3.Issue Book\n4.View Book List\n5.Go Back");
	printf("\nEnter the Choice : ");
        scanf("%d",&choice);
	switch(choice){

		case 1:AddBooks();
		    	break;
		case 2:RemoveBooks();
			   break;
		case 3:	IssueBooks();
		        break;
		case 4:ViewBooks();
                break;
		case 5:return;
		default:printf("\nInvalid Option\n");

	}

	}



}




int main(){
	int choice;
	printf("+++++++++++++++++++++++++++++++++++++++++++++LIBRARY MANAGMENT+++++++++++++++++++++++++++++++++++++++++++++\n\n");
	while(1){
	printf("\nSelect From the Options \n\n1.Student\n2.Librarian\n3.Exit\n\n");

        printf("Enter your Choice : ");
	scanf("%d",&choice);

	switch(choice){

		case 1: displayStudentOption();
			break;
		case 2:displayLibrarianOption();
			break;
		case 3: exit(0);
		        break;
		default:printf("\nInvalid Choice\n\n ");

	}
	}



return 0;
}



