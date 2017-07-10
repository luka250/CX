#include <bits/stdc++.h>
using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int daxta_kochi=1,x,bMark[13][15][20][5];
string s;

//input:
int ngroups[13];
int speVis[5][10];
int nSubject;

map<pair<string,pair<int,int> >,int> mpTeacher;
map<string,int> mpTeacherLesson;
map<string,int> ::iterator it;
priority_queue<pair<int,string> > pr;
map<string,int> mpRec;

string subject[30];

map<string,int> mpSubject;

struct {
	int nGroup;
	int nLessonDay;
	int nSubject[30];
}grade[13];

struct {
	string teacher1;
	string teacher2;
	string teacher3;
	int vis[5];
}group[13][15][30];

int nLongDay[13][15];
int fixGroupSubject[13][15][30];

//output:
string timetable[13][15][5][10];

cogy(int a,int b,int c){
	for(int i=4;i>0;i--)
		for(int j=0;j<grade[a].nLessonDay+min(1,nLongDay[a][b]);j++)
			if(speVis[i][j]==0&&group[a][b][c].vis[i]==0&&mpTeacher[{group[a][b][c].teacher1,{i,j}}]==0&&timetable[a][b][i][j]==""){
				group[a][b][c].vis[i]++,speVis[i][j]++;if(j==grade[a].nLessonDay)nLongDay[a][b]--;mpTeacher[{group[a][b][c].teacher1,{i,j}}]++;timetable[a][b][i][j]=subject[c];return 0;}
	memset(speVis,0,sizeof(speVis));cogy(a,b,c);
}

fil1(int a,int b,int c,int alto){
	for(int i=0;i<5;i++)
		for(int j=0;j<grade[a].nLessonDay+alto*min(1,nLongDay[a][b]);j++)
			if(timetable[a][b][i][j]==""&&group[a][b][c].vis[i]==0)
				if(mpTeacher[{group[a][b][c].teacher1,{i,j}}]==0)
					if(mpTeacher[{group[a][b][c].teacher2,{i,j}}]==0||group[a][b][c].teacher2=="x")
						if(mpTeacher[{group[a][b][c].teacher3,{i,j}}]==0||group[a][b][c].teacher3=="x"){
							group[a][b][c].vis[i]++;timetable[a][b][i][j]=subject[c];if(j==grade[a].nLessonDay)nLongDay[a][b]--;
							mpTeacher[{group[a][b][c].teacher1,{i,j}}]++;mpTeacher[{group[a][b][c].teacher2,{i,j}}]++;mpTeacher[{group[a][b][c].teacher3,{i,j}}]++;
							return 0;}
	return 1;
}

fil2(int a,int b,int c,int belo){
	for(int i=0;i<5;i++)
		for(int j=0;j<grade[a].nLessonDay+belo*min(1,nLongDay[a][b])-1;j++)
			if(timetable[a][b][i][j]==""&&timetable[a][b][i][j+1]==""&&group[a][b][c].vis[i]==0)
				if(mpTeacher[{group[a][b][c].teacher1,{i,j}}]==0&&mpTeacher[{group[a][b][c].teacher1,{i,j+1}}]==0)
					if((mpTeacher[{group[a][b][c].teacher2,{i,j}}]==0&&mpTeacher[{group[a][b][c].teacher2,{i,j+1}}]==0)||group[a][b][c].teacher2=="x")
						if((mpTeacher[{group[a][b][c].teacher3,{i,j}}]==0&&mpTeacher[{group[a][b][c].teacher3,{i,j+1}}]==0)||group[a][b][c].teacher3=="x"){
							group[a][b][c].vis[i]++;timetable[a][b][i][j]=subject[c];timetable[a][b][i][j+1]=subject[c];if(j==grade[a].nLessonDay-1)nLongDay[a][b]--;
							mpTeacher[{group[a][b][c].teacher1,{i,j}}]++;mpTeacher[{group[a][b][c].teacher2,{i,j}}]++;mpTeacher[{group[a][b][c].teacher3,{i,j}}]++;
							mpTeacher[{group[a][b][c].teacher1,{i,j+1}}]++;mpTeacher[{group[a][b][c].teacher2,{i,j+1}}]++;mpTeacher[{group[a][b][c].teacher3,{i,j+1}}]++;
							return 0;}
	return 1;
}

rec(int a,int b,int c,int d,string s){
	while(daxta_kochi){
		
		int i=0,j=0;
		
		if(bMark[a][b][c][d]!=0){
				timetable[a][b][(bMark[a][b][c][d]-1)/5][(bMark[a][b][c][d]-1)%5]="";group[a][b][c].vis[(bMark[a][b][c][d]-1)/5]=0;
				mpTeacher[{group[a][b][c].teacher1,{(bMark[a][b][c][d]-1)/5,(bMark[a][b][c][d]-1)%5}}]=0;bMark[a][b][c][d]=0;
		}
		
		if(grade[a].nGroup==0){
			if(a==12)daxta_kochi=0;
			else mpRec[s+"x"]++,rec(a+1,b,6,0,"");
		}
		if(grade[a].nSubject[c]==0){
				mpRec[s+"x"]++;
				if(d<grade[a].nSubject[c]-1)rec(a,b,c,d+1,s+patch::to_string(bMark[a][b][c][d]));
				else if(c<nSubject)rec(a,b,c+1,0,s+patch::to_string(bMark[a][b][c][d]));
				else if(b<grade[a].nGroup)rec(a,b+1,6,0,s+patch::to_string(bMark[a][b][c][d]));
				else if(a<12)rec(a+1,1,6,0,s+patch::to_string(bMark[a][b][c][d]));
				else daxta_kochi=0;
		}
			
		if(fixGroupSubject[a][b][c]==0){
			
			while(i<5){
				while(j<grade[a].nLessonDay){
					if(timetable[a][b][i][j]==""&&mpTeacher[{group[a][b][c].teacher1,{i,j}}]==0&&group[a][b][c].vis[i]==0&&mpRec[s+patch::to_string(i*5+j+1)]==0){
						timetable[a][b][i][j]=subject[c];group[a][b][c].vis[i]++;
						mpTeacher[{group[a][b][c].teacher1,{i,j}}]++;bMark[a][b][c][d]=5*i+j+1;
						break;
					}
					j++;
				}j=0;i++;if(bMark[a][b][c][d]!=0)break;
			}i=0;
			if(bMark[a][b][c][d]==0){
				while(i<5){
					while(j<grade[a].nLessonDay+min(1,nLongDay[a][b])){
						if(timetable[a][b][i][j]==""&&mpTeacher[{group[a][b][c].teacher1,{i,j}}]==0&&group[a][b][c].vis[i]==0&&mpRec[s+patch::to_string(i*5+j+1)]==0){
							timetable[a][b][i][j]=subject[c];group[a][b][c].vis[i]++;if(j==grade[a].nLessonDay)nLongDay[a][b]--;
							mpTeacher[{group[a][b][c].teacher1,{i,j}}]++;bMark[a][b][c][d]=5*i+j+1;
							break;
						}
						j++;
					}j=0;i++;if(bMark[a][b][c][d]!=0)break;
				}
			}
				if(bMark[a][b][c][d]!=0){mpRec[s+patch::to_string(bMark[a][b][c][d])]++;
				if(d<grade[a].nSubject[c]-1)rec(a,b,c,d+1,s+patch::to_string(bMark[a][b][c][d]));
				else if(c<nSubject)rec(a,b,c+1,0,s+patch::to_string(bMark[a][b][c][d]));
				else if(b<grade[a].nGroup)rec(a,b+1,6,0,s+patch::to_string(bMark[a][b][c][d]));
				else if(a<12)rec(a+1,1,6,0,s+patch::to_string(bMark[a][b][c][d]));
				else daxta_kochi=0;
			}
			else break;
		}
		else{
			if(mpRec[s+"x"]!=0)break;
			else mpRec[s+"x"]++;
			if(d<grade[a].nSubject[c]-1)rec(a,b,c,d+1,s+patch::to_string(bMark[a][b][c][d]));
				else if(c<nSubject)rec(a,b,c+1,0,s+patch::to_string(bMark[a][b][c][d]));
				else if(b<grade[a].nGroup)rec(a,b+1,6,0,s+patch::to_string(bMark[a][b][c][d]));
				else if(a<12)rec(a+1,1,6,0,s+patch::to_string(bMark[a][b][c][d]));
				else daxta_kochi=0;
		}
	}
}

main(){cout<<"INPUT"<<endl;
	cin>>nSubject;
	
	for(int i=1;i<=nSubject;i++){
		cin>>s;
		subject[i]=s;
		mpSubject[s]=i;
	}
	
	for(int i=1;i<13;i++){
		cin>>grade[i].nGroup>>x;
		grade[i].nLessonDay=x/5;
		for(int j=1;j<=nSubject;j++)
			cin>>grade[i].nSubject[j];
		for(int j=1;j<=grade[i].nGroup;j++)
			nLongDay[i][j]=x%5;
	}
	
	for(int i=1;i<13;i++)
		for(int j=1;j<=grade[i].nGroup;j++)
			for(int l=1;l<=nSubject;l++){
				cin>>s;
				group[i][j][l].teacher1=s;mpTeacherLesson[s]+=grade[i].nSubject[l];
				cin>>s;
				group[i][j][l].teacher2=s;mpTeacherLesson[s]+=grade[i].nSubject[l];
				cin>>s;
				group[i][j][l].teacher3=s;mpTeacherLesson[s]+=grade[i].nSubject[l];
			}x=0;
	
	it=mpTeacherLesson.begin();
	
	while(it!=mpTeacherLesson.end()){
		pr.push({it->second,it->first});
		it++;
	}if(pr.top().second=="x")pr.pop();
	
	for(int j=5;j<13;j++)
		for(int l=1;l<=grade[j].nGroup;l++)
			for(int ii=4;ii<=nSubject;ii++)
				if(x<mpTeacherLesson.size()/4)if(pr.top().second==group[j][l][ii].teacher1||pr.top().second==group[j][l][ii].teacher2||pr.top().second==group[j][l][ii].teacher3){
					if(grade[j].nSubject[ii]==4){
						if(fil2(j,l,ii,0)==1)fil2(j,l,ii,1);if(fil1(j,l,ii,0)==1)fil1(j,l,ii,1);if(fil1(j,l,ii,0)==1)fil1(j,l,ii,1);
					}
					else{
						for(int jj=0;jj<grade[j].nSubject[ii]-4;jj++)
							if(fil2(j,l,ii,0)==1)fil2(j,l,ii,1);
						for(int jj=0;jj<grade[j].nSubject[ii]-max(0,2*(grade[j].nSubject[ii]-4));jj++)
							if(fil1(j,l,ii,0)==1)fil1(j,l,ii,1);
					}
					fixGroupSubject[j][l][ii]++;pr.pop();x++;
				}
	x=0;
	
	for(int i=1;i<13;i++)
		for(int j=1;j<=grade[i].nGroup;j++)
			for(int l=0;l<grade[i].nSubject[1];l++)
				cogy(i,j,1);
	memset(speVis,0,sizeof(speVis));
	
	for(int i=1;i<13;i++)
		for(int j=1;j<=grade[i].nGroup;j++)
			for(int l=0;l<grade[i].nSubject[2];l++)
				cogy(i,j,2);
	memset(speVis,0,sizeof(speVis));
	
	for(int i=1;i<13;i++)
		for(int j=1;j<=grade[i].nGroup;j++)
			for(int l=0;l<grade[i].nSubject[3];l++)
				cogy(i,j,3);
		
	for(int i=1;i<5;i++)
		for(int j=1;j<=grade[i].nGroup;j++)
			for(int l=3;l<=nSubject;l++){
				if(grade[i].nSubject[l]==4){
					if(fil2(i,j,l,0)==1)fil2(i,j,l,1);if(fil1(i,j,l,0)==1)fil1(i,j,l,1);if(fil1(i,j,l,0)==1)fil1(i,j,l,1);
				}
				else{
					for(int ii=0;ii<grade[i].nSubject[l]-4;ii++)
						if(fil2(i,j,l,0)==1)fil2(i,j,l,1);
					for(int ii=0;ii<grade[i].nSubject[l]-max(0,2*(grade[i].nSubject[l]-4));ii++)
						if(fil1(i,j,l,0)==1)fil1(i,j,l,1);
				}
			}
			
	for(int i=5;i<13;i++)
		for(int j=1;j<=grade[i].nGroup;j++)
			for(int l=4;l<6;l++)
				if(fixGroupSubject[i][j][l]==0){
					if(grade[i].nSubject[l]==4){
						if(fil2(i,j,l,0)==1)fil2(i,j,l,1);if(fil1(i,j,l,0)==1)fil1(i,j,l,1);if(fil1(i,j,l,0)==1)fil1(i,j,l,1);
					}
					else{
						for(int ii=0;ii<grade[i].nSubject[l]-4;ii++)
							if(fil2(i,j,l,0)==1)fil2(i,j,l,1);
						for(int ii=0;ii<grade[i].nSubject[l]-max(0,2*(grade[i].nSubject[l]-4));ii++)
							if(fil1(i,j,l,0)==1)fil1(i,j,l,1);
					}
				}
				x=0;
	rec(5,1,6,0,"");
			
	cout<<endl<<"OUTPUT"<<endl;
					
	for(int i=0;i<13;i++)
		for(int j=1;j<=grade[i].nGroup;j++){cout<<i<<"^"<<j<<" "<<"klasi"<<endl;
			for(int l=0;l<5;l++){cout<<endl;
				for(int o=0;o<grade[i].nLessonDay+1;o++)
					cout<<timetable[i][j][l][o]<<endl;
				}
			}
}
