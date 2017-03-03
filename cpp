#include <bits/stdc++.h>
using namespace std;

int i,j,l,o,info,spo;

int teacher[200];//number of lessons for each teacher
map<string,int> teacherID;//IDs of teachers
pair<int,int> nl[13][20];//nuber of lessons per day for each class+number of long days
set<int> cfr[5][7];//list of free rooms at any moment

//input
int ncg[12];//number of classes on each grade
int m[12][20][20][3];//[grade][number][subject][teacher]
int nol[12][20];//number of lessons of each subject on each grade per week
int comp1,comp2,gym;//speacial rooms
int nr,room[500];//rooms
int mp_tfixed[200];//rooms fixed to teachers
int mp_cfixed[12][20];//rooms fixed to classes
//output
typedef struct {
	int subject;
	int teacher1;
	int teacher2;
	int teacher3;
	int room1;
	int room2;
	int room3;
}timetable[13][20][5][7];

computerize(int c){int x=0,y=0;[Error] expected unqualified-id before '[' token

	while(i<12){
		if(nol[i][info]>0){
			while(j<ncg[i]){
				if(y<nl[i][j].first)timetable[i][j][x][y].subject=info,timetable[i][j][x][y].teacher1=m[i][j][info],timetable[i][j][x][y].room1=c;
				else {x++,y=0;if(x==5)break;if(y<nl[i][j].first)timetable[i][j][x][y].subject=info,timetable[i][j][x][y].teacher1=m[i][j][info],timetable[i][j][x][y].room1=c;}
				j++;y++;
			}j=0;i++;
		}
	}
}

main(){
	
	while(i<5){
		while(j<7){
			while(l<nr){
				cfr[i][j].insert(room[l]);
				l++;
			}l=0;j++;
		}j=0;i++;
	}i=0;//filling set cfr
	
	while(i<13){
		while(j<20){
			while(l<20){
				while(m[i][j][l][o]!=0){
					teacher[m[i][j][l][o]]++;
					o++;
				}o=0;l++;
			}l=0;j++;
		}j=0;i++;
	}i=0;//count number of lessons for each teacher per week
	
	computerize(comp1);if(comp2!=0)computerize(comp2);i=0;j=0;
}