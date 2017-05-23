#include<fstream.h>
#include<ctype.h>
#include<string.h>
#include<dos.h>
#include<stdio.h>
#include<conio.h>
void draw_line(int r)
{
	for(int i=1; i<=80; i++)
	{
		gotoxy(i, r);
		cout << "Ä";
	}
}
class item
{
	int itemno;
	char itemname[25];
	char category[40];
	char type[30];
	int price;
	char avail;
	public:
		void get_item();
		void disp_all(int r);
		void show_modify_details();
		void show_avail_details();
		void change_avail();
      void update_details(int n, char nm[25], char c[40], char t[30], int p);
		int return_itemno();
		int return_price();
		char *return_iname();
		char *return_cat();
		char *return_type();
		char return_avail();
};
void change()
{
	item i;
	int ino = 0, pr = 0, c=0;
	char inm[25], cat[40], tp[30], st='Y';
	ofstream fout;
	ifstream fin;
	fin.open("ritem.dat",ios::binary);
	fin.seekg(0,ios::beg);
	fout.open("tempitem.dat",ios::binary);
	while(fin.read((char*)&i,sizeof(item)))
	{
		ino = i.return_itemno();
		strcpy(inm,i.return_iname());
		strcpy(cat,i.return_cat());
		strcpy(tp,i.return_type());
		pr = i.return_price();
		st = i.return_avail();
		i.change_avail(ino,inm,cat,tp,pr,st);
		fout.write((char*)&i,sizeof(item));
		c=c+1;
	}
	fin.close();
	fout.close();
	cout << "\n Number of records : "<< c;
}               */
int item :: return_itemno()
{
	return itemno;
}
int item :: return_price()
{
	return price;
}
char * item :: return_iname()
{
	return itemname;
}
char * item :: return_cat()
{
	return category;
}
char * item :: return_type()
{
	return type;
}
char item :: return_avail()
{
	return avail;
}
void item :: change_avail()
{
	if(avail == 'Y')
	{
		avail = 'N';
	}
	else
	{
		avail = 'Y';
	}
}
void item :: update_details(int n, char nm[25], char c[40], char t[30], int p)
{
	itemno = n;
	if(strlen(nm) > 0)
		strcpy(itemname,nm);
	if(strlen(c) > 0)
		strcpy(category,c);
	if(strlen(t) > 0)
		strcpy(type,t);
	price = p;
	avail = 'Y';
}
int generate_itemno()
{
	int c=0;
	item i;
	ifstream file;
	file.open("ritem.dat",ios::binary);
	file.seekg(0,ios::beg);
	while(file.read((char*)&i,sizeof(item)))
	{
		c = c + 1;
	}
	file.close();
	return(c+1);
}

void item :: get_item()
{
	int l=0, f;
	itemno = generate_itemno();
	gotoxy(15, 6);
	cout << "Item Number";
	gotoxy(15, 8);
	cout << "Item Name";
	gotoxy(15,10);
	cout << "Category";
	gotoxy(15,12);
	cout << "Type";
	gotoxy(15, 14);
	cout << "Price";
	gotoxy(35, 6);
	cout << itemno;
	do
	{
		gotoxy(35, 8);
		gets(itemname);
		l = strlen(itemname);
		if(l == 0)
		{
			gotoxy(15, 23);
			cout << "Item Name cannot be blank...........";
			getch();
			gotoxy(15, 23);	clreol();
			gotoxy(35, 8); 	clreol();
		}
	}while(l == 0);
	do
	{
		gotoxy(35,10);
		gets(category);
		l = strlen(category);
		if(l == 0)
		{
			gotoxy(15, 23);
			cout << "Category cannot be blank...........";
			getch();
			gotoxy(15, 23);	clreol();
			gotoxy(35, 10);	clreol();
		}
	}while(l == 0);
	do
	{
		f = 1;
		gotoxy(20, 23);
		cout << "TYPE: veg or nonveg";
		gotoxy(35, 12);
		gets(type);
		l = strlen(type);
		gotoxy(20,23);	clreol();
		if(l == 0)
		{
			gotoxy(15, 23);
			cout << "Type cannot be blank...........";
			getch();
			gotoxy(15, 23);	clreol();
			gotoxy(35, 12);	clreol();
		}
		if((strcmp(type,"veg") != 0) && (strcmp(type,"nonveg") != 0))
		{
			f = 0;
			gotoxy(20,23);	clreol();
			gotoxy(20,23);
			cout << "Type can be only veg or nonveg";
			getch();
			gotoxy(20, 23);	clreol();
			gotoxy(35, 12); clreol();

		}
	}while(l == 0 || f == 0);
	do
	{
		gotoxy(35, 14);
		cin >> price;
		if(price <= 0)
		{
			gotoxy(15, 23);
			cout << "Price should be greater than 0";
			getch();
			gotoxy(15, 23);
			clreol();
			gotoxy(35,14);
			clreol();
		}
	}while(price <= 0);
	avail = 'Y';
}
void item :: disp_all(int r)
{
	gotoxy(4, r);
	cout << itemno;
	gotoxy(13, r);
	cout << itemname;
	gotoxy(35, r);
	cout << category;
	gotoxy(55, r);
	cout << type;
	gotoxy(65, r);
	cout << price;
	gotoxy(75, r);
	cout << avail;
}
void item :: show_modify_details()
{
	gotoxy(32, 8);
	cout << itemno;
	gotoxy(32, 10);
	cout << itemname;
	gotoxy(32, 12);
	cout << category;
	gotoxy(32, 14);
	cout << type;
	gotoxy(32, 16);
	cout << price;
}
void item :: show_avail_details()
{
	gotoxy(52, 8);
	cout << itemno;
	gotoxy(52, 10);
	cout << itemname;
	gotoxy(52, 12);
	cout << category;
	gotoxy(52, 14);
	cout << type;
	gotoxy(52, 16);
	cout << price;
	gotoxy(52, 18);
	cout << avail;
}

int validate_itemno(int ino)
{
	int no=0, flag = 0;
	item i;
	ifstream file;
	file.open("ritem.dat",ios::binary);
	file.seekg(0,ios::beg);
	while(file.read((char*)&i,sizeof(item)))
	{
		no = i.return_itemno();
		if(no == ino)
			flag = 1;
	}
	file.close();
	return flag;
}
void modify_item()
{
	clrscr();
	int ino, flag = 0, i, offset = 0, pr;
	char ans, inm[25], cat[40], typ[30];
	item ob;
	fstream file;
	file.open("ritem.dat",ios::binary|ios::in|ios::out);
	do
	{
		gotoxy(10, 12);
		cout << "Enter Item no to be modified (0 to quit) : ";
		cin >> ino;
		if(ino > 0)
		{
			flag = validate_itemno(ino);
			if(flag == 0)
			{
				gotoxy(10, 23);
				cout << "Invalid Item Number, please try again";
				getch();
				gotoxy(10, 23);
				clreol();
				gotoxy(10, 12);
				clreol();
			}
		}
	}while(flag == 0 && ino != 0);
	if(ino > 0)
	{
	clrscr();
	gotoxy(30, 3);
	cout << "MODIFY ITEM DETAILS";
	for(i=10; i<=70; i++)
	{
		gotoxy(i, 5);
		cout << "Ä";
		gotoxy(i, 7);
		cout << "Ä";
		gotoxy(i, 18);
		cout << "Ä";
		gotoxy(i, 20);
		cout << "Ä";
	}
	for(i=6; i<=19; i++)
	{
		gotoxy(10, i);
		cout << "³";
		gotoxy(70, i);
		cout << "³";
		if(i<=17)
		{
			gotoxy(30, i);
			cout << "³";
			gotoxy(50, i);
			cout << "³";
		}
	}
	gotoxy(10, 5); cout << "Ú";
	gotoxy(70, 5); cout << "¿";
	gotoxy(10,20); cout << "À";
	gotoxy(70,20); cout << "Ù";
	gotoxy(10, 7); cout << "Ã";
	gotoxy(70, 7); cout << "´";
	gotoxy(10, 18); cout << "Ã";
	gotoxy(70, 18); cout << "´";
	gotoxy(30, 5); cout << "Â";
	gotoxy(50, 5); cout << "Â";
	gotoxy(30,18); cout << "Á";
	gotoxy(50,18); cout << "Á";
	gotoxy(30,7); cout << "Å";
	gotoxy(50,7); cout << "Å";
	gotoxy(12, 6);
	cout << "PARTICULARS";
	gotoxy(33, 6);
	cout << "CURRENT DETAILS";
	gotoxy(55, 6);
	cout << "NEW DETAILS";
	gotoxy(12, 8);
	cout << "Item Number";
	gotoxy(12, 10);
	cout << "Item Name";
	gotoxy(12, 12);
	cout << "Category";
	gotoxy(12, 14);
	cout << "Type";
	gotoxy(12, 16);
	cout << "Price";
	offset = ((ino-1)*sizeof(item));
	file.seekg(offset,ios::beg);
	file.read((char*)&ob,sizeof(item));
	ob.show_modify_details();
	gotoxy(15, 19);
	cout << "DO YOU WANT TO MODIFY THIS ITEM [Y/N] : ";
	cin >> ans;
	ans = toupper(ans);
	if(ans == 'Y')
	{

		gotoxy(52, 8);
		cout << ino;
		gotoxy(15, 23);
		cout << "If you DON'T want to change then Just Press ENTER";
		gotoxy(52, 10);
		gets(inm);
		gotoxy(52, 12);
		gets(cat);
		gotoxy(52, 14);
		gets(typ);
		gotoxy(15, 23);
		clreol();
		do
		{
			gotoxy(52, 16);
			cin >> pr;
			if(pr <= 0)
			{
				gotoxy(15, 23);
				cout << "PRICE SHOULD BE GREATER THEN 0";
				getch();
				gotoxy(15, 23);
				clreol();
				for(i=52; i<=55; i++)
				{
					gotoxy(i, 16);
					cout << " ";
				}
			}
		}while(pr <= 0);
		offset = 0;
		offset = ((ino-1) * (sizeof(item)));
		ob.update_details(ino, inm, cat, typ, pr);
		file.seekp(offset,ios::beg);
		file.write((char*)&ob,sizeof(item));
		file.close();
	}
	}
}
void change_availability()
{
	clrscr();
	int ino, flag = 0, i, offset = 0, pr;
	char inm[25], cat[40], typ[30];
	char ans;
	item ob;
	fstream file;
	file.open("ritem.dat",ios::binary|ios::in|ios::out);
	do
	{
		gotoxy(10, 12);
		cout << "Enter Item no (0 to Quit) : ";
		cin >> ino;
		if(ino > 0)
		{
			flag = validate_itemno(ino);
			if(flag == 0)
			{
			gotoxy(10, 23);
			cout << "Invalid Item Number, please try again";
			getch();
			gotoxy(10, 23);
			clreol();
			gotoxy(10, 12);
			clreol();
			}
		}
	}while(flag == 0 && ino != 0);
	if(ino > 0)
	{
	clrscr();
	gotoxy(30, 3);
	cout << "ITEM DETAILS";
	for(i=10; i<=70; i++)
	{
		gotoxy(i, 5);
		cout << "Ä";
		gotoxy(i, 7);
		cout << "Ä";
		gotoxy(i, 20);
		cout << "Ä";
		gotoxy(i, 22);
		cout << "Ä";
	}
	for(i=6; i<=21; i++)
	{
		gotoxy(10, i);
		cout << "³";
		gotoxy(70, i);
		cout << "³";
		if(i<=19)
		{
		gotoxy(50, i);
		cout << "³";
		}
	}
	gotoxy(10, 5); cout << "Ú";
	gotoxy(70, 5); cout << "¿";
	gotoxy(10,22); cout << "À";
	gotoxy(70,22); cout << "Ù";
	gotoxy(10, 7); cout << "Ã";
	gotoxy(70, 7); cout << "´";
	gotoxy(10, 20); cout << "Ã";
	gotoxy(70, 20); cout << "´";
	gotoxy(50, 5); cout << "Â";
	gotoxy(50,20); cout << "Á";
	gotoxy(50,7); cout << "Å";
	gotoxy(25, 6);
	cout << "PARTICULARS";
	gotoxy(55, 6);
	cout << "DETAILS";
	gotoxy(12, 8);
	cout << "Item Number";
	gotoxy(12, 10);
	cout << "Item Name";
	gotoxy(12, 12);
	cout << "Category";
	gotoxy(12, 14);
	cout << "Type";
	gotoxy(12, 16);
	cout << "Price";
	gotoxy(12, 18);
	cout << "Available";
	offset = ((ino-1)*sizeof(item));
	file.seekg(offset,ios::beg);
	file.read((char*)&ob,sizeof(item));
	ob.show_avail_details();
	gotoxy(15, 21);
	cout << "WANT TO CHANGE AVAILABILITY OF THIS ITEM [Y/N] : ";
	cin >> ans;
	ans = toupper(ans);
	if(ans == 'Y')
	{
		offset = 0;
		offset = ((ino-1)*sizeof(item));
		file.seekp(offset,ios::beg);
		ob.change_avail();
		file.write((char*)&ob,sizeof(item));
		file.close();
	}
	}
}
void write_item()
{
	clrscr();
	gotoxy(34, 2);
	cout << "ADD NEW ITEM";
	item i;
	ofstream file;
	file.open("ritem.dat",ios::binary|ios::app);
	i.get_item();
	file.write((char*)&i,sizeof(item));
	file.close();

}
void read_allitems()
{
	clrscr();
	int r;
	item i;
	ifstream file;
	file.open("ritem.dat",ios::binary);
	file.seekg(0,ios::beg);
	gotoxy(32,2);
	cout << "ALL ITEM'S DETAIL";
	draw_line(3);
	gotoxy(2,4);
	cout << "Item No.";
	gotoxy(15,4);
	cout << "Item Name";
	gotoxy(35,4);
	cout << "Category";
	gotoxy(55,4);
	cout << "Type";
	gotoxy(65,4);
	cout << "Price";
	gotoxy(74,4);
	cout << "Avail";
	draw_line(5);
	draw_line(21);
	r = 7;
	while(file.read((char*)&i,sizeof(item)))
	{
		i.disp_all(r);
		r++;
		if(r == 21)
		{
			gotoxy(15, 23);
			cout << "Press any key to Continue...........";
			getch();
			gotoxy(15, 23);
			clreol();
			r = 7;
			for(int j=7; j<=20; j++)
			{
				gotoxy(1, j);
				clreol();
			}
		}
	}
	file.close();
	getch();
}
void read_items(int ch)
{
	clrscr();
	int r;
	char a='Y';
	item i;
	ifstream file;
	file.open("ritem.dat",ios::binary);
	file.seekg(0,ios::beg);
	gotoxy(32,2);
	if(ch == 3)
	{
		cout << "AVAILABLE ITEMS";
	}
	else
	{
		cout << "NOT AVAILABLE ITEMS";
	}
	draw_line(3);
	gotoxy(2,4);
	cout << "Item No.";
	gotoxy(15,4);
	cout << "Item Name";
	gotoxy(35,4);
	cout << "Category";
	gotoxy(55,4);
	cout << "Type";
	gotoxy(65,4);
	cout << "Price";
	gotoxy(74,4);
	cout << "Avail";
	draw_line(5);
	draw_line(21);
	r = 7;
	while(file.read((char*)&i,sizeof(item)))
	{
		a = i.return_avail();
		if(ch == 3 && a == 'Y')
		{
			i.disp_all(r);
			r++;
		}
		else if(ch == 4 && a == 'N')
		{
			i.disp_all(r);
			r++;
		}
		if(r == 21)
		{
			gotoxy(15, 23);
			cout << "Press any key to Continue...........";
			getch();
			gotoxy(15, 23);
			clreol();
			r = 7;
			for(int j=7; j<=20; j++)
			{
				gotoxy(1, j);
				clreol();
			}
		}
	}
	file.close();
	getch();
}

struct dt
{
	int d, m, y;
};
class bill
{
	int billno;
	dt bdt;
	int noi;
	int itemno[10];
	int total;
	float tax_amt;
	float billamt;
	public:
		bill()
		{
			total=0;
			tax_amt=0;
			billamt=0;
		}
		void bill_details();
		dt return_date();
		float return_billamt();
		void print_details(int r);
};
int getbillno()
{
	int c=0;
	bill b;
	ifstream file;
	file.open("rbill.dat",ios::binary);
	file.seekg(0,ios::beg);
	while(file.read((char*)&b,sizeof(bill)))
	{
		c = c + 1;
	}
	file.close();
	return(c+1);
}
dt bill :: return_date()
{
	return bdt;
}
float bill :: return_billamt()
{
	return billamt;
}
void bill :: bill_details()
{
	clrscr();
	struct date d;
	item g;
	int i, j, c, itno, v, p,k=8,qty,amt;
	gotoxy(38, 3);
	cout << "BILL";
	billno = getbillno();
	gotoxy(11, 4);
	cout << "Bill No. : "<<billno;
	getdate(&d);
	bdt.d = d.da_day;
	bdt.m = d.da_mon;
	bdt.y = d.da_year;
	gotoxy(53, 4);
	cout << "Date : "<<bdt.d<<"/"<<bdt.m<<"/"<<bdt.y;
	do
	{
		gotoxy(10, 20);
		cout << "Enter Number of items : ";
		cin >> noi;
		if(noi <=0 || noi > 10)
		{
			gotoxy(10, 24);
			cout << "No. of Items has to be between 1 & 10";
			getch();
			gotoxy(10, 24);
			clreol();
			gotoxy(10, 20);
			clreol();
		}
	}while(noi <= 0 || noi > 10);
	gotoxy(10, 20); clreol();

	for(i=10; i<=70; i++)
	{
		gotoxy(i, 5);
		cout << "Ä";
		gotoxy(i, 7);
		cout << "Ä";
		gotoxy(i, 18);
		cout << "Ä";
		gotoxy(i, 23);
		cout << "Ä";
	}
	for(i=6; i<=22; i++)
	{
		gotoxy(10, i);
		cout << "³";
		gotoxy(70, i);
		cout << "³";
		gotoxy(58, i);
		cout << "³";
		if(i<=17)
		{
			gotoxy(19, i);
			cout << "³";
			gotoxy(45, i);
			cout << "³";
			gotoxy(52, i);
			cout << "³";
		}
	}
	gotoxy(10, 5); cout << "Ú";
	gotoxy(70, 5); cout << "¿";
	gotoxy(10,23); cout << "À";
	gotoxy(70,23); cout << "Ù";
	gotoxy(10, 7); cout << "Ã";
	gotoxy(10,18); cout << "Ã";
	gotoxy(70, 7); cout << "´";
	gotoxy(70,18); cout << "´";
	gotoxy(19, 5); cout << "Â";
	gotoxy(45, 5); cout << "Â";
	gotoxy(52, 5); cout << "Â";
	gotoxy(58, 5); cout << "Â";
	gotoxy(19,18); cout << "Á";
	gotoxy(45,18); cout << "Á";
	gotoxy(52,18); cout << "Á";
	gotoxy(58,23); cout << "Á";
	gotoxy(19,7); cout << "Å";
	gotoxy(45,7); cout << "Å";
	gotoxy(52,7); cout << "Å";
	gotoxy(58,7); cout << "Å";
	gotoxy(58,18); cout << "Å";
	gotoxy(12, 6);cout << "ItemNo";
	gotoxy(27, 6);cout << "Item Name";
	gotoxy(47, 6);cout << "Rate";
	gotoxy(54, 6);cout << "Qty";
	gotoxy(62, 6);cout << "Amount";
	k=8;
	for(i=0;i<noi;i++)
	{
		ifstream fin;
		fin.open("ritem.dat",ios::binary);
		fin.seekg(0,ios::beg);
		gotoxy(14, k);
		cin>>itno;
		while(fin.read((char*)&g,sizeof(item)))
		{
			v=g.return_itemno();
			if(itno==v)
			{
				gotoxy(24, k);cout<<g.return_iname();
				p=g.return_price();
				gotoxy(48, k);cout<<p;

			}
		}
		fin.close();
		gotoxy(55,k);
		cin>>qty;
		amt=p*qty;
		gotoxy(63, k);cout<<amt;
		total=total+amt;

		k=k+1;
	}
	gotoxy(47,19);cout<<"Sub Total";
	gotoxy(62,19);cout<<total;
	tax_amt=(total*4)/100;
	gotoxy(47,20);cout<<"Sales Tax";
	gotoxy(62,20);cout<<tax_amt;
	billamt=total+tax_amt;
	gotoxy(47,22);cout<<"GROSS TOTAL";
	gotoxy(62,22);cout<<billamt;
	getch();
}
void bill :: print_details(int r)
{
	gotoxy(12, r);
	cout << billno;
	gotoxy(27, r);
	cout << total;
	gotoxy(42, r);
	cout << tax_amt;
	gotoxy(57, r);
	cout << billamt;
}
void write_bill()
{
	ofstream file;
	bill b;
	char ans;
	file.open("rbill.dat",ios::binary|ios::app);
	b.bill_details();
	gotoxy(15,24);
	cout<<"Do you want to SAVE this Bill [Y/N] : ";
	cin >> ans;
	gotoxy(15,24);
	clreol();
	ans = toupper(ans);
	if(ans == 'Y')
	{
		file.write((char*)&b,sizeof(bill));
		gotoxy(20, 24);
		cout << "Bill Saved...........";
		getch();
	}
	file.close();
}
void daily_report()
{
	clrscr();
	float tc=0.0,ba=0.0;
	int i, r;
	struct date d;
	getdate(&d);
	dt gd, td;
	td.d = d.da_day;
	td.m = d.da_mon;
	td.y = d.da_year;
	ifstream file;
	bill b;
	gotoxy(25,2);
	cout << "TOTAL COLLECTION ON "<<td.d<<"-"<<td.m<<"-"<<td.y;
	for(i=1; i<=79; i++)
	{
		gotoxy(i, 5);
		cout << "Ä";
		gotoxy(i, 7);
		cout << "Ä";
		gotoxy(i, 21);
		cout << "Ä";
		gotoxy(i, 23);
		cout << "Ä";
	}
	gotoxy(10,6);
	cout << "Bill Number";
	gotoxy(25, 6);
	cout << "Gross Amount";
	gotoxy(40, 6);
	cout << "Sales Tax";
	gotoxy(55, 6);
	cout << "Net Amount";
	file.open("rbill.dat",ios::binary);
	file.seekg(0,ios::beg);
	r = 8;
	while(file.read((char*)&b,sizeof(bill)))
	{
		gd = b.return_date();
		if(gd.d == td.d && gd.m == td.m && gd.y == td.y)
		{
			b.print_details(r);
			ba = b.return_billamt();
			tc = tc + ba;
			r = r + 1;
		}
	}
	file.close();
	gotoxy(40, 22);
	cout << "TOTAL";
	gotoxy(57, 22);
	cout << tc;
	getch();
}

void item_menu()
{
	int ch;
	do
	{
		clrscr();
		gotoxy(35, 5);
		cout << "ITEM MENU";
		gotoxy(30, 7);
		cout << "1  Add New Item";
		gotoxy(30, 9);
		cout << "2  Display All Items";
		gotoxy(30, 11);
		cout << "3  Display Available Items";
		gotoxy(30, 13);
		cout << "4  Display Not Available Items";
		gotoxy(30, 15);
		cout << "5  Modify Price";
		gotoxy(30, 17);
		cout << "6  Change Availability";
		gotoxy(30, 19);
		cout << "7  Exit";
		gotoxy(31, 21);
		cout << "Enter Task Number : ";
		cin >> ch;
		switch(ch)
		{
			case 1: write_item();
				break;
			case 2: read_allitems();
				break;
			case 3:
			case 4: read_items(ch);
				break;
			case 5: modify_item();
				break;
			case 6: change_availability();
				break;
		}
	}while(ch < 7);

}

void main_menu()
{
	int ch;
	do{
		clrscr();
		gotoxy(35, 5);
		cout<<"MAIN MENU";
		gotoxy(30,10);
		cout<<"1  Item Menu";
		gotoxy(30,12);
		cout<<"2  Bill Details";
		gotoxy(30,14);
		cout<<"3  Daily Report";
		gotoxy(30,16);
		cout<<"4  Exit";
		gotoxy(31,22);
		cout<<"Enter choice number : ";
		cin>>ch;
		switch(ch)
		{
			case 1: item_menu();
			break;
			case 2: write_bill();
			break;
			case 3: daily_report();
			break;

		}
	  }while(ch < 4);
}
void main()
{
	clrscr();
	main_menu();
	getch();
}