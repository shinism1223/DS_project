#pragma once
#pragma warning (disable : 4996)
#include<fstream>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<set>
#define oo 0x3fffffff
using namespace std;


struct User {
	string id_name, sc_name;
	vector<string> tweet;
};

vector<User> all_users;
vector<set<int> > inedge;
vector<set<int> > outedge;
vector<int> outdegree;
vector<int> indegree;
vector<int> user_tweet_cnt;
vector<int> above_users;

int n = 0,edge_n=0,tweet_n=0;

map<string, int> word_tweet_cnt;
map<string, map<int,int> > word_map;

int my_cmp(string a, string b);
void pre_processing();
void user_parcer();
void user_renumbering();
void my_sort();
void friend_parcer();
void word_parcer();
int find_user(string s);
void kosaraju();
void dijkstra(int st);
void dfs(int x);
void ndfs(int x);
void upheap(int x);
void downheap(int x);

void action0();
void action1();
void action2();
void action3();
void action4();
void action5();
void action6();
void action7();
void action8();
void action9();

int main()
{
	user_parcer();
	pre_processing();
	user_renumbering();
	friend_parcer();
	word_parcer();
	int action;
	while (1) {
		printf("Press action(0 ~ 9 , 99 : Quit) : ");
		scanf("%d", &action);

		if (action == 0) {
			action0();
		}
		else if (action == 1) {
			action1();
		}
		else if (action == 2) {
			action2();
		}
		else if (action == 3) {
			action3();
		}
		else if (action == 4) {
			action4();
		}
		else if (action == 5) {
			action5();
		}
		else if (action == 6) {
			action6();
		}
		else if (action == 7) {
			action7();
		}
		else if (action == 8) {
			action8();
		}
		else if (action == 9) {
			action9();
		}
		else if (action == 99) {
			printf("Quit\n");
			break;
		}
		else printf("ERROR\n");
	}



	return 0;
}


void action0() {
	printf("Total users : %d\n", n);
	printf("Total friendship records : %d\n", edge_n);
	printf("Total tweets : %d\n\n", tweet_n);
}

void action1()
{
	int i;
	int sum, max, min;

	sum = max = min = indegree[0];

	for (i = 1; i < n; i++) {
		sum += indegree[i];
		if (max < indegree[i]) max = indegree[i];
		if (min > indegree[i]) min = indegree[i];
	}
	printf("Average number of friends : %.2lf\n", ((double)sum) / ((double)n));
	printf("Minimum friends : %d\n", min);
	printf("Maximum number of friends : %d\n\n", max);


	sum = max = min = user_tweet_cnt[0];

	for (i = 1; i < n; i++) {
		sum += user_tweet_cnt[i];
		if (max < user_tweet_cnt[i]) max = user_tweet_cnt[i];
		if (min > user_tweet_cnt[i]) min = user_tweet_cnt[i];
	}
	printf("Average tweets per user: %.2lf\n", ((double)sum) / ((double)n));
	printf("Minium tweets per user :%d\n", min);
	printf("Maximu tweets per user : %d\n\n", max);
}

void action2()
{
	int i,j,mx;
	string ms[6];

	map<string, int>::iterator it ;

	for (i = 0; i < 5;i++){
		mx = 0;
		for (it = word_tweet_cnt.begin(); it != word_tweet_cnt.end() ; ++it) {
			for (j = 0; j < i; j++) if ((*it).first.compare(ms[j])==0) break;
			if (j == i && mx < (*it).second) {
				mx = (*it).second;
				ms[i] = (*it).first;
			}
		}
		printf("max - %d : \n",i+1);
		printf("Word : %s \n",ms[i].data());
		printf("cnt : %d \n\n",mx);
	}
}

void action3()
{
	int i, mxi[6], mx,j, k;

	for (i = 0; i < 5; i++) {
		mx = 0;	
		for (j = 0; j < n;j++) {
			for (k = 0; k < i; k++) if (j== mxi[k]) break;
			if (k == i && mx< user_tweet_cnt[j]) {
				mx= user_tweet_cnt[j];
				mxi[i] = j;
			}
		}
		printf("max - %d : \n", i + 1);
		printf("User ID Name : %s\n",all_users[mxi[i]].id_name.data());
		printf("User Screen Name : %s\n", all_users[mxi[i]].sc_name.data());
		printf("cnt : %d\n\n",mx);
	}
}

void action4()
{
	char c;
	string s;
	int p;

	c = getc(stdin);
	while (1) {
		c = getc(stdin);
		if (c == '\n') break;
		s.push_back(c);
	}

	if (word_map.find(s) == word_map.end()) {
		printf("ERROR : No word here\n");
		return;
	}

	map<int,int>::iterator it = word_map[s].begin();

	above_users.clear();

	for (; it != word_map[s].end(); ++it) {
		p = (*it).first;
		above_users.push_back(p);
		printf("User ID name : %s\n", all_users[p].id_name.data());
		printf("User Screen name : %s\n\n", all_users[p].sc_name.data());
	}

}

void action5()
{
	int i,p;
	int q;

	for (i = 0; i < above_users.size();i++) {
		p = above_users[i];
		for (set<int>::iterator it = inedge[p].begin(); it!=inedge[p].end(); ++it) {
			q = (*it);
			printf("User ID name : %s\n", all_users[q].id_name.data());
			printf("User Screen name : %s\n\n", all_users[q].sc_name.data());

		}
	}
}

void action6()
{
	char c;
	string s;
	int p, i;

	c = getc(stdin);
	while (1) {
		c = getc(stdin);
		if (c == '\n') break;
		s.push_back(c);
	}

	if (word_map.find(s) == word_map.end()) {
		printf("ERROR : No word here\n");
		return;
	}

	tweet_n -= word_tweet_cnt[s];
	word_tweet_cnt.erase(s);
	map<int,int>::iterator it;
	for (it = word_map[s].begin(); it!=word_map[s].end(); ++it) {
		p = (*it).first;
		user_tweet_cnt[p] -= (*it).second;
	}
	word_map.erase(s);

	printf("deleted\n");
}

void action7()
{
	char c;
	string s;
	int p;
	int pp;

	c = getc(stdin);
	while (1) {
		c = getc(stdin);
		if (c == '\n') break;
		s.push_back(c);
	}

	if (word_map.find(s) == word_map.end()) {
		printf("ERROR : No word here\n");
		return;
	}
	vector<string> del;
	map<int, int>::iterator itpp;
	for (itpp = word_map[s].begin(); itpp != word_map[s].end(); ++itpp) {
		del.push_back(all_users[(*itpp).first].id_name);
	}

	vector<string>::iterator it;
	for (it = del.begin(); it != del.end(); ++it) {
		p = find_user((*it));
		
		set<int>::iterator itq;
		int q;
		for (itq=inedge[p].begin(); itq!=inedge[p].end(); ++itq) {
			q = (*itq);
			outedge[q].erase(p);
			outdegree[q]--;
		}
		edge_n -= indegree[p];

		pp=p;
		vector<set<int> >::iterator it1 = inedge.begin();
		for (; pp >= 0; pp--) ++it1;
		inedge.erase(it1);

		pp = p;
		vector<int>::iterator it11 = indegree.begin();
		for (; pp >= 0; pp--) ++it11;
		indegree.erase(it11);


		for (itq = outedge[p].begin(); itq != outedge[p].end(); ++itq) {
			q = (*itq);
			inedge[q].erase(p);
			indegree[q]--;
		}
		edge_n -= outdegree[p];

		pp = p;
		vector<set<int> >::iterator it2 = outedge.begin();
		for (; pp >= 0; pp--) ++it2;
		outedge.erase(it2);

		pp = p;
		vector<int>::iterator it22 = outdegree.begin();
		for (; pp >= 0; pp--) ++it22;
		outdegree.erase(it22);


		pp = p;
		vector<int>::iterator it99 = user_tweet_cnt.begin();
		for (; pp >= 0; pp--) ++it99;
		user_tweet_cnt.erase(it99);


		string l;
		vector<string>::iterator its;
		for (its = all_users[p].tweet.begin(); its != all_users[p].tweet.end(); ++its) {
			l = (*its);
			word_tweet_cnt[l]--;
			if(l!=s && word_map.find(l)!=word_map.end()) word_map[l].erase(p);
		}
		
		pp = p;
		vector<User>::iterator it3 = all_users.begin();
		for (; pp >= 0; pp--) ++it3;
		all_users.erase(it3);

		n--;
	}

	word_map.erase(s);
}

int v;
vector<int> check;
vector<int> func;
vector<vector<int> > scc;
void kosaraju()
{
	int i;

	v = 0;
	check.clear();
	check.resize(n+10);
	
	scc.clear();
	scc.resize(n + 10);

	for (i = 0; i < n; i++) check[i] = 0;

	func.clear();

	for (i = 0; i < n; i++) {
		if (check[i] == 0) dfs(i);
	}

	check.clear();
	check.resize(n + 10);
	for (i = 0; i < n; i++) check[i] = 0;

	for (i = n - 1; i >= 0; i--) {
		if (check[func[i]] == 0) {
			ndfs(func[i]);
			v++;
		}
	}
}

void dfs(int x)
{
	int p;

	check[x] = 1;
	set<int>::iterator it;
	for (it = outedge[x].begin(); it != outedge[x].end(); ++it) {
		p = (*it);
		if (check[p] == 0) dfs(p);
	}
	func.push_back(x);
}

void ndfs(int x)
{
	int p;

	check[x] = 1;
	scc[v].push_back(x);
	set<int>::iterator it;
	for (it = inedge[x].begin(); it != inedge[x].end(); ++it) {
		p = (*it);
		if (check[p] == 0) ndfs(p);
	}
}

void action8()
{
	int i, a[6],j,k,mx;
	kosaraju();

	for (i = 0; i < 5; i++) {
		mx = 0; a[i] = -1;
		for (j = 0; j < v; j++) {
			for (k = 0; k < i; k++) if (a[k] == j) break;
			if (k == i && mx < scc[j].size()) {
				mx = scc[j].size();
				a[i] = j;
			}
		}

		printf("max scc %d :\n", i+1);
		if (a[i] == -1) {
			printf("not exist\n");
			continue;
		}
		printf("cnt : %d\n", mx);
		for (j = 0; j < scc[a[i]].size(); j++) {
			k=scc[a[i]].at(j);
			printf("id : %s\n", all_users[k].id_name.data());
		}
		printf("\n");
	}
	printf("\n");

}


vector<int> dst;
vector<int> heap;
vector<int> hloc;
int hn;

void my_swap(int &a, int &b)
{
	int tp;
	tp = a;
	a = b;
	b = tp;
}


void upheap(int x)
{
	while (x>1) {
		if (dst[heap[x / 2]] <= dst[heap[x]]) return;
		hloc[heap[x]] = x / 2;
		hloc[heap[x / 2]] = x;
		my_swap(heap[x], heap[x / 2]);
		x /= 2;
	}
}

void downheap(int x)
{
	int k;
	while (x * 2 <= hn) {
		k = x * 2;
		if (k + 1 <= hn && dst[heap[k]]>dst[heap[k + 1]]) {
			k++;
		}
		if (dst[heap[k]] >= dst[heap[x]]) return;
		hloc[heap[x]] = k;
		hloc[heap[k]] = x;
		my_swap(heap[x], heap[k]);
		x = k;
	}
}

void dijkstra(int st)
{
	int i, j;
	int x, y;

	dst.clear();
	heap.clear();
	hloc.clear();
	dst.resize(n + 10);
	heap.resize(n + 10);
	hloc.resize(n + 10);

	for (i = 0; i < n; i++) {
		dst[i] = oo;
		heap[i + 1] = i;
		hloc[i] = i + 1;
	}
	
	dst[st] = 0;
	upheap(hloc[st]);
	hn = n;
	for (int z = 0; z < n; z++) {
		x = heap[1];
		hloc[heap[1]] = hn;
		hloc[heap[hn]] = 1;
		my_swap(heap[1], heap[hn]);
		hn--;
		downheap(1);
		set<int>::iterator it;
		for (it = outedge[x].begin(); it != outedge[x].end(); ++it) {
			y = (*it);
			if (dst[x] + indegree[y] < dst[y]) {
				dst[y] = dst[x] + indegree[y];
				upheap(hloc[y]);
			}
		}
	}
}


void action9()
{
	char c;
	string s;
	int p;

	c = getc(stdin);
	while (1) {
		c = getc(stdin);
		if (c == '\n') break;
		s.push_back(c);
	}

	p = find_user(s);
	if (p== -1) {
		printf("ERROR : No user here\n");
		return;
	}

	dijkstra(p);

	int min,a[6];
	int i, j, k;
	for (i = 0; i < 5; i++) {
		min = oo; a[i] = -1;
		for (j= 0; j < n; j++) {
			for (k = 0; k < i; k++) if (a[k] == j) break;
			if (k == i && min > dst[j]) {
				min = dst[j];
				a[i] = j;
			}
		}

		printf("min dst %d : \n", i + 1);
		if (a[i] == -1) {
			printf("not exist\n");
			continue;
		}
		printf("dst : %d\n", min);
		printf("user ID : %s\n", all_users[a[i]].id_name.data());
	}
	printf("\n");
}








void pre_processing()
{
	int i;
	indegree.resize(n + 10);
	outdegree.resize(n + 10);
	inedge.resize(n + 10);
	outedge.resize(n + 10);
	user_tweet_cnt.resize(n + 10);
	above_users.clear();

	for (i = 0; i < n; i++) indegree[i] = outdegree[i] = user_tweet_cnt[i] = 0;
}

void word_parcer()
{
	FILE *word_in;
	word_in = fopen("word.txt", "r");
	int x,v;
	char c;
	user_tweet_cnt.resize(n + 10);
	for (int i = 0; i < n; i++) user_tweet_cnt[i] = 0;
	while (1) {
		string id;
		while (1) {
			c = fgetc(word_in);
			if (c == '\n' || c == -1) break;
			id.push_back(c);
		}
		if (c == -1) break;

		while (1) {
			c = fgetc(word_in);
			if (c == '\n' || c == -1) break;
		}
		if (c == -1) break;
		
		string word;
		while (1) {
			c = fgetc(word_in);
			if (c == '\n' || c == -1) break;
			word.push_back(c);
		}

		x = find_user(id);
		user_tweet_cnt[x] ++;
		word_tweet_cnt[word] ++;
		if (word_map.find(word) != word_map.end()){
			if (word_map[word].find(x) != word_map[word].end()) v = word_map.at(word).at(x)+1;
			else v = 1;
		}
		else v = 1;
		pair<int, int> k;
		k.first = x;
		k.second = v;
		word_map[word].insert(k);

		all_users[x].tweet.push_back(word);


		tweet_n++;
		if (c == -1) break;
		c = fgetc(word_in);
		if (c == -1) break;
	}

	fclose(word_in);
}

void friend_parcer()
{
	FILE *friend_in;
	friend_in = fopen("friend.txt", "r");
	char c;
	int x, y;

	while (1) {
		string id1;
		while (1) {
			c = fgetc(friend_in);
			if (c == '\n' || c == -1) break;
			id1.push_back(c);
		}
		if (c == -1) break;

		string id2;
		while (1) {
			c = fgetc(friend_in);
			if (c == '\n' || c == -1) break;
			id2.push_back(c);
		}

		x=find_user(id1);
		y = find_user(id2);

		indegree[y]++;
		outdegree[x]++;
		inedge[y].insert(x);
		outedge[x].insert(y);

		edge_n++;
		if (c == -1) break;
		c = fgetc(friend_in);
		if (c == -1) break;
	}

	fclose(friend_in);
}

int find_user(string s) 
{
	int st=0,ed=n-1,md,kk;
	string ms;

	while (st<=ed) {
		md = (st + ed) / 2;
		ms = all_users[md].id_name;
		kk = my_cmp(ms, s);
		if(kk==0){
			return md;
		}else if(kk>0){
			ed = md - 1;
		}
		else {
			st = md + 1;
		}
	}

	return -1;
}

int my_cmp(string a, string b)
{
	if (a.size() < b.size()) return -1;
	else if (a.size() > b.size()) return 1;

	if (a.compare(b) > 0) return 1;
	else if (a.compare(b) < 0) return -1;
	return 0;
}

void user_parcer()
{
	FILE *user_in;
	user_in = fopen("user.txt", "r");
	char c;
	while (1) {
		string id_name;
		while (1) {
			c = fgetc(user_in);
			if (c == '\n' || c == -1) break;
			id_name.push_back(c);
		}
		if (c == -1) break;

		while (1) {
			c = fgetc(user_in);
			if (c == '\n' || c == -1) break;
		}
		if (c == -1) break;

		string sc_name;
		while (1) {
			c = fgetc(user_in);
			if (c == '\n' || c == -1) break;
			sc_name.push_back(c);
		}
		
		User p;
		p.id_name = id_name;
		p.sc_name = sc_name;
		all_users.push_back(p);
		n++;
		if (c == -1) break;
		c = fgetc(user_in);
		if (c == -1) break;
	}

	fclose(user_in);
}

void user_renumbering()
{
	my_sort();
}

void my_sort()
{
	int i,j;
	User tp;

	for (i = 0;i<n;i++) {
		for (j = i + 1; j < n; j++) {
			if (my_cmp(all_users[i].id_name,all_users[j].id_name)>0){
				tp = all_users[i];
				all_users[i] = all_users[j];
				all_users[j] = tp;
			}
		}
	}
}