#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

struct item{
	char name[20];
	char type[15];
	int jumlah;
	int harga;
	struct item *next, *prev;
}*temp ,*head, *tail;


struct item *createItem(char name[], char type[], int jumlah, int harga){
	struct item *data = (struct item*)malloc(sizeof(struct item));
	strcpy(data->name, name);
	if(strcmp(type,"yes")==0){
		strcpy(data->type, "Coffee");
	}
	else {
		strcpy(data->type,"non-Coffee");
	}
	data->jumlah = jumlah;
	data->harga = harga;
	data->next = data->prev = NULL;
	return data;
}

void insertItem(char name[], char type[], int jumlah, int harga){
	struct item *data = createItem(name, type, jumlah, harga);
	if(head==NULL){
		head = tail = data;
	}
	else{
		tail->next = data;
		data->prev = tail;
		tail = data;
	}
}

struct keranjang{
	char name[20];
	char type[15];
	int jumlah;
	int harga;
	struct keranjang *next, *prev;
}*tempK, *headK, *tailK;

struct keranjang *createK(char name[], char type[], int jumlah, int harga){
	struct keranjang *newK = (struct keranjang*)malloc(sizeof(struct keranjang));
	strcpy(newK->name, name);
	strcpy(newK->type, type);
	newK->jumlah = jumlah;
	newK->harga = harga;
	
	newK->next = newK->prev = NULL;
	return newK;
}

void insertK(char name[], char type[], int jumlah, int harga){
	struct keranjang *cart = createK(name, type, jumlah, harga);
	if(headK==NULL){
		headK = tailK = cart;
	}
	else{
		tailK->next = cart;
		cart->prev = tailK;
		tailK = cart;
	}
}

int sudahAda(char name[]){
	tempK = headK;
	while(tempK){
		if(strcmp(tempK->name,name)==0){
			return 1;
		}
		tempK = tempK->next;
	}
	return 0;
}

void menu(){
	printf("\n\tWelcome to Brew Coffee Shop\n");
	printf("\tselect role:\n");
	printf("\t1. Admin\n");
	printf("\t2. Customer\n");
	printf("\t3. Exit\n\t");
}

void displayMenu(){
	printf("\n\t=======================================================================");
	printf("\n\tNo. | Menu                 | Type          | Quantity |     Price     |");
	printf("\n\t-----------------------------------------------------------------------\n");
	temp = head;
	int i=0;
	while(temp!=NULL){
		i++;
		printf("\t%-3d | %-20s | %13s | %8d |    %-10d |\n",i, temp->name, temp->type, temp->jumlah, temp->harga);
		temp = temp->next;
	}
	printf("\t-----------------------------------------------------------------------\n");
}
void displayOrder(){
	printf("\tYour Order:\n");
	printf("\n\t=======================================================================");
	printf("\n\tNo. | Menu                 | Type          | Quantity |  Total Price  |");
	printf("\n\t-----------------------------------------------------------------------\n");
	tempK = headK;
	int i=0;
	while(tempK){
		i++;
		printf("\t%-3d | %-20s | %13s | %8d |    %-10d |\n",i, tempK->name, tempK->type, tempK->jumlah, tempK->harga);
		tempK = tempK->next;
	}
	printf("\t-----------------------------------------------------------------------\n");
}

void customerMenu(){
	printf("\t1. Buy item\n");
	printf("\t2. Cancel item\n");
	printf("\t3. Exit or Purchase item\n");
	printf("\t_______________________________________________________________________\n");
}

void adminMenu(){
	printf("\t1. Add item\n");
	printf("\t2. remove item\n");
	printf("\t3. Exit\n");
}


int main(){
	insertItem("Americano", "yes", 24, 19000);
	insertItem("Chocolate Baked", "no", 15, 24000);
	insertItem("Alberto", "yes", 7, 44000);
	int jumlahItem = 3;
	int pilihan;
	do{
		system("cls");
		menu();
		printf("Masukkan pilihan: ");
		scanf("%d",&pilihan);getchar();	
		switch(pilihan){
			case 1:{
				system("cls");
				printf("\n\tSelamat datang Mr./Mrs. Admin");
				displayMenu();
				int pilih;
				do{
					adminMenu();
					printf("\tMasukkan pilihan[1-3]: ");
					scanf("%d",&pilih);getchar();
					switch(pilih){
						case 1:{
							char name[25];
							int pjgNama;
							do{
								printf("\tMasukkan nama item[5-20]: ");
								scanf("%[^\n]",name);getchar();
								pjgNama = strlen(name);
							}while(pjgNama<5 || pjgNama>20);
							
							char type[5];
							do{
								printf("\tTipe Kopi[yes/no]: ");
								scanf("%s",type);
							}while(strcmp(type,"yes")!=0 && strcmp(type,"no")!=0);
							
							int jumlah;
							do{
								printf("\tMasukkan jumlah item[1-100]: ");
								scanf("%d",&jumlah);getchar();
							}while(jumlah<1 || jumlah>100);
							
							int harga;
							do{
								printf("\tMasukkan harga item[20.000-200.000]: ");
								scanf("%d",&harga);getchar();
							}while(harga<20000 || harga>200000);
							insertItem(name,type,jumlah,harga);
							jumlahItem++;
							printf("\tBerhasil menambahkan item");
							printf("\n\tPress any key to continue...");
							getchar();
							
							system("cls");
							displayMenu();
							break;
						}
						case 2:{
							int pilih;
							do{
								printf("\tpilih item yang ingin dibuang[1-%d]: ",jumlahItem);
								scanf("%d",&pilih);getchar();
							}while(pilih<1 || pilih>jumlahItem);
							
							temp=head;
							int i=1;
							while(pilih>i){
								temp=temp->next;
								i++;
							}
							if(temp==head){
								head = head->next;
								free(temp);
							}
							else if(temp==tail){
								if(tail==head){
									free(temp);
								}
								else{
									tail=tail->prev;
									tail->next=NULL;
									free(temp);
								}
							}
							else{
								temp->prev->next=temp->next;
								temp->next->prev=temp->prev;
								free(temp);
							}
							printf("\tItem sudah dibuang");
							jumlahItem--;
							getchar();
							
							system("cls");
							displayMenu();
							break;
						}	
					}
					
				}while(pilih!=3);
				printf("\n\tPress any key to continue...");
				getchar();
				break;
			}
			case 2:	{
				system("cls");
				char nama[20];
				printf("\n\n\tMasukkan nama: ");
				scanf("%s",&nama);
				printf("\n\tSelamat datang di Brew coffee Shop, Mr./ Mrs. %s",nama);
				int pilih;
				int menudiOrder=0;
				do{
					if (menudiOrder==0) displayMenu();
					customerMenu();
					printf("\tMasukkan pilihan[1-3]: ");
					scanf("%d",&pilih);getchar();
					switch(pilih){
						case 1:	{
							printf("\tPilih menu[1-%d]: ",jumlahItem);
							int choice;
							scanf("%d",&choice);getchar();
							temp = head;
							for(int i=1; i<choice; i++){
								temp = temp->next;
							}
							if(temp->jumlah==0){
								printf("\tstock habis");
								break;
							}
							int jumla;
							do{
								printf("\tMasukkan jumlah[1-%d]: ",temp->jumlah);
								scanf("%d",&jumla);getchar();
							}while(jumla<1||jumla>temp->jumlah);
							temp->jumlah = temp->jumlah-jumla;
							int nn = sudahAda(temp->name);
							if(nn==1) {
								tempK = headK;
								while(strcmp(tempK->name,temp->name)!=0){
									tempK = tempK->next;
								}
								tempK->jumlah = tempK->jumlah+jumla;
								tempK->harga = tempK->harga+(temp->harga*jumla);
							}
							else if(nn==0) insertK(temp->name,temp->type,jumla,temp->harga*jumla);
							system("cls");
							displayMenu();
							displayOrder();
							menudiOrder=1;
							continue;
							}
						case 2:	{
							if(headK==NULL){
								system("cls");
								printf("\n\t\*Maaf Menu belum diorder\n");
								printf("\n\tPress any key to continue...");
								getchar();
								system("cls");
								continue;
							}	
							else{
								while(headK){
									tempK = headK;
									temp = head;
									while(temp){
										if(strcmp(temp->name, tempK->name)==0){
											temp->jumlah =  temp->jumlah+tempK->jumlah;
										}
										temp = temp->next;
									}
									headK = headK->next;
									free(tempK);
									tempK = NULL;
								}
								menudiOrder=0;
								system("cls");
							}
							continue;	
						}	
					}
				}while(pilih!=3);
				if(pilih==3){
					if(headK){
						system("cls");
						int total=0;
						tempK = headK;
						if(tempK){
							total = total + tempK->harga;
							tempK = tempK->next;
						}	
						printf("\n\tYour bills is %d",total);
						printf("\n\tThankyou for buying our coffee, have a nice day :)");
						while(headK){
							tempK = headK;
							headK = headK->next;
							free(tempK);
							tempK = NULL;
						}
					}
					else break;
				}
				printf("\n\tPress any key to continue...");
				getchar();
				break;
			}
		}
	}while(pilihan!=3);
	if(pilihan==3){
		system("cls");
		printf("\n\n\tThankyou :)\n");
	}
	return 0;
}
