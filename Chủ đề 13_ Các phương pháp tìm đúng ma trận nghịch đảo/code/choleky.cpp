#include<iostream>
#include<math.h>
#include <fstream>
using namespace std;
//-------------------xay dung lop so phuc voi cac phep toan don gian---------------//
struct p
{
    double iThuc;
    double iAo;
};



//-------------------cong hai so phuc--------------------//
p operator +(p a,p b)
{ p c;
c.iThuc=a.iThuc+b.iThuc;
c.iAo=a.iAo+b.iAo;
return c;
};


//-----------------------tru 2 so phuc--------------------//
p operator -(p a,p b)
{ p c;
c.iThuc=a.iThuc-b.iThuc;
c.iAo=a.iAo-b.iAo;
return c;
};



//-------------nhan 2 so phuc-------------------//
p operator *(p a,p b)
{   p c;
   c.iThuc=a.iThuc*b.iThuc-a.iAo*b.iAo;
    c.iAo=a.iThuc*b.iAo+a.iAo*b.iThuc;
    return c;
};



//------------phep chia 2 so phuc----------------//
p operator/(p b,p a)
{ p c;
    c.iThuc=(a.iThuc*b.iThuc+a.iAo*b.iAo)/(pow(a.iThuc,2)+pow(a.iAo,2));
    c.iAo=(a.iThuc*b.iAo-a.iAo*b.iThuc)/(pow(a.iThuc,2)+pow(a.iAo,2));
    return c;
}
 
//---------------kiem tra ma tran  co doi xung k-------------------------//
 	bool kiem_tra_ma_tran_doi_xung(p a[100][100],int n)	
 	{
 		for(int i=0;i<n;i++)
 			for(int j=0;j<n;j++)
 				if(a[i][j].iThuc!=a[j][i].iThuc)
 				return 0;
 				 return 1;}
	 
	void tim_ma_tran_tam_giac( p a[100][100],p b[100][100],int n)
//-----------------------------A=St*S-tim ma tran tam giac A=Bt*B---------------------------------------------------------------------//		
  	{ int i,j,k;
	b[0][0].iThuc=sqrt(a[0][0].iThuc);
	for( i=1;i<n;i++)
		b[0][i].iThuc=a[0][i].iThuc/b[0][0].iThuc;
		
	for( i=1;i<n;i++)
	{
		p acc;
		 acc.iThuc=0;
		 acc.iAo=0;
		for(k=0;k<i;k++)
		 	{
				 acc=acc+b[k][i]*b[k][i];
			 }
		if((a[i][i].iThuc-acc.iThuc)<0)	 
	     b[i][i].iAo=sqrt(acc.iThuc-a[i][i].iThuc);
		else b[i][i].iThuc=sqrt(a[i][i].iThuc-acc.iThuc);
		if (b[i][i].iAo==0&&b[i][i].iThuc==0)
		 { cout<<"ma tran khong kha nghich";
	        break;}
	
		for( j=i+1;j<n;j++)
			{		p acc;
		 acc.iThuc=0;
		 acc.iAo=0;
				for( k=0;k<i;k++)
					{
						acc=acc+b[k][i]*b[k][j];
						}
		
				b[i][j]=(a[i][j]-acc)/b[i][i]	;
			  
				}
	}}
//-----------------------------------tim ma tran nghich dao----------------------------------------------------------//
void ma_tran_nghich_dao(p b[100][100],p b1[100][100],int n )
{
   int i,j,k;
 	for( i=0;i<n;i++)
 	{ p x;
 	  x.iThuc=1;
	 b1[i][i]=x/b[i][i];}
 	for(j=1;j<n;j++)
 	 for( i=0;i<j;i++)
 	 	{   p x;
 	 	  x.iThuc=-1;
		    p acc;
				   acc.iAo=0;
				   acc.iThuc=0;
 	 		for( k=0;k<j;k++)
 	 			{
			
				   acc=acc+b1[i][k]*b[k][j];
 	 			}
 	 			
 	   		b1[i][j]=x*(acc/b[j][j]);
   
		}}
		
//------------------------------------------ma_tran_chuyen_vi-------------------------------------//
void ma_tran_chuyen_vi(p b1[100][100], p bt[100][100],int n)
{
		int i,j,k;
		for(i=0;i<n;i++)
		 	for( j=0;j<n;j++)
			   bt[i][j]=b1[j][i];
			   }
			   
//---------------------------------------------nhan_ma_tran-----------------------------------------//
void nhan_ma_tran(p b1[100][100], p bt[100][100], p c[100][100],int n)
{    int i,j,k,h;
	for(  h=0;h<n;h++)
	 {
	 for( k=0;k<n;k++)
    	{ c[h][k].iAo=0;
    	c[h][k].iThuc=0;
		for( i=0;i<n;i++)
   			 {
				c[h][k]= b1[h][i]*bt[i][k]+c[h][k];
			}
		}
		}

				}

//----------------------------------in ma tran nghich dao cua a--------------------------//
void in_ma_tran(p c[100][100],int n)
   {for(int i=0;i<n;i++)
 	{	{for(int j=0;j<n;j++)
 		  cout <<c[i][j].iThuc<<"     ";
		   }
 	cout<<endl;
 		}
	}
	
	//------------doc du lieu tu file--------------------------//
	void read(int &n,p a[100][100])
{   

ifstream  f("C:/Users/ACER/Desktop/hongtran.txt" );
  f>> n;
for(int i=0;i<n;i++)
	{
	for(int j=0;j<n;j++)
  		 f>>a[i][j].iThuc;
}
f.close();
  		 
}
//-------------------------------ghi du lieu ra file------------------------------------//
void write(int n,p a[100][100])
{   
	ofstream f;
  f.open("C:/Users/ACER/Desktop/hongtran.txt", ios::app );
  f<<"\n\n\n";
  f<<"ma tran nghich dao la\n";
  for(int i=0;i<n;i++)
	{
	for(int j=0;j<n;j++)
  		 {
		   f<<a[i][j].iThuc;
  		 f<<"  ";}
  		 f<<"\n";
		   }
  	f.close();
}			   		
int main()
{
//--------------------------------------nhap ma tran A---------------------------------------------------------------------------//
    p a[100][100];
    int n;
    read(n,a);
    cout<<"nhap kich thuoc ma tran";
    cout<<n<<endl;
    cout<<"  cac ptu cua ma tran  "<<endl;
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
       		cout<<a[i][j].iThuc;
    
	if(kiem_tra_ma_tran_doi_xung(a,n))
	  { p b[100][100],b1[100][100],bt[100][100],a1[100][100];
	    tim_ma_tran_tam_giac(a,b,n);
	    ma_tran_nghich_dao(b,b1,n);
	    ma_tran_chuyen_vi(b1,bt,n);
	    nhan_ma_tran(b1,bt,a1,n);
	    cout<<"ma tran nghich dao la"<<endl;
	    in_ma_tran(a1,n);
	    write(n,a1);
		   }
	    else 
	    { p at[100][100],b[100][100],btamgiac[100][100],btamgiac1[100][100],bt[100][100],b1[100][100],a1[100][100];
	     ma_tran_chuyen_vi(a,at,n);
	     nhan_ma_tran(at,a,b,n); // b=at*a;
	     tim_ma_tran_tam_giac(b,btamgiac,n);
	     ma_tran_nghich_dao(btamgiac,btamgiac1,n);
	     ma_tran_chuyen_vi(btamgiac1,bt,n);
	     nhan_ma_tran(btamgiac1,bt,b1,n);
	     nhan_ma_tran(b1,at,a1,n);
	     cout<<"ma tran nghich dao la"<<endl;
	     in_ma_tran(a1,n);
	     write(n,a1);
	       }
 }
	   	
