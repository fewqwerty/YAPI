#include <stdio.h>
#include <stdlib.h >  
#include <string.h>
#pragma warning(disable : 4996)


int l = 0, select=0, strok=0, um=0;
int** matritsa; int** matritsa_dev; int** matritsa_dev_f;
int know[6];

int malloc_all = 0, calloc_all = 0, free_all = 0;
int malloc_vvod = 0, calloc_vvod = 0, free_vvod = 0, free_v1 = 0;
int malloc_os = 0, calloc_os = 0, free_os = 0,realloc_os=0;

enum divise 
{
	radio,
	tachograph,
	gps,
	glonass,
	gsm,
	cam
};
int proverka(char* y) // проверка для енам дивайс
{
	//printf("1 %s 1\n ", y); 
	char* com[6] =
	{
		"radio", "tachograph", "gps", "glonass", "gsm", "cam"
	};
	for (int i = 0; i < 6; i++) {
		if (strcmp(y, com[i]) == 0) return i ;
	}
	return -1;
}
int f_proverka(const char* y) { //проверка для команд 
	const char *com[6] =
	{
		"insert", "select", "delete", "update", "uniq", "exit"
	};
	for (int i = 0; i < 6; i++) {
		if (strcmp(y, com[i]) == 0) return i + 1;
	}
	return -1;
}
int insert_proverka(char *y){
	//printf("%s\n", y);
	char* com[7] = {
		"car_vendor=", "car_model=", "car_year=", "car_id=", "divise=", "carrying=", "axles="
	}; int q = 0; 
	while (q< 20) {
		
		if (y[q] == '=') { 
			 break;
		}
		q++;
	}
	q++;
	
	for (int i = 0; i < 7; i++) {
		if (strncmp(y, com[i], q) == 0) return i + 1;
	}
	//printf("%d ", q);
	return -1;
}
int proverka_yes(char* y) {
	
	char* com[11] = {
		"car_vendor", "car_model", "car_year", "car_id", "divise", "carrying", "axles", "include", "in","items","status"
	}; 
	for (int i = 0; i < 11; i++) {
		if (strcmp(y, com[i]) == 0) return i + 1;
	}
	//if ((strncmp(y, com[8], 7) == 0)) return 8;
	return -1;
}
void forenum(char *y){
	
	for (int i = 0; i < 6; i++) {
		know[i] = 0;
	}
	int jj = strlen(y); int flag=0;
	char* save_y = (char*)calloc(jj, sizeof(char)); calloc_os++;
	for (int i = 0; i < jj; i++) {
		if (y[i] == ',') flag++;
		save_y[i] = y[i];
	}
	
	
	if (flag > 0) {
		char* coma = (char*)calloc(flag, sizeof(char)); calloc_os++;
		for (int i = 0; i < flag; i++) {
			coma[i] = ',';
			//printf("%c ", coma[i]);
		}

		char* q = strtok(y, coma);
		while (q != NULL) {
			int t = proverka(q);
			if (t == -1) break;
			know[t] = 1;

			q = strtok(NULL, coma);
			//printf("q-%s ", q);
			
		}
		free(coma);
		free_os++;
	}
	if (flag == 0) {
		int t = proverka(y);
		if (t != -1) {
			know[t] = 1;
		}
		
	}
	for (int i = 0; i < jj; i++) y[i] = save_y[i];
	free(save_y); free_os++;
	
}
int lin_search(int* y) {
	for (int q = 0; q < 6; q++) {
		if (y[q] == 1) return q;	
    }
	if (y[5] != 1) return -1;

}
int lin_search_ver(int* y) {
	for (int q = 0; q < l; q++) {
		if (y[q] == 1) return q;
	}
	if (y[5] != 1) return -1;
}
int lin(int l) {
	for (int q = l - 1; q >= 1; q--) {
		if (matritsa[q][0] == 0) return q;
	}
	if (matritsa[l-1][0] != 0) return -1;
}
int analiz(int flag, int l,int q){
	int deleete = -1;
	int proverka = 0;
	for (int i = 1; i < l; i++) {
		for (int j = 0; j < 7; j++) {
			if (matritsa[i][j] == 0) proverka++;
			if (j == 6) {
				if (proverka == flag) {
					for (int q = 0; q < 7; q++) matritsa[i][q] = 0;
					proverka = 0;
					deleete++;
				}
				else {
					proverka = 0;
					for (int q = 0; q < 7; q++) matritsa[i][q] = 1;
				}
			}
		}
	}
	
	if (q == 1) {
		int d = lin(l);
		if (d != -1) {
			for (int j = 0; j < 7; j++) matritsa[d][j] = 1;
		}
		else return -1;
	}
	
	return deleete;
}

typedef struct snode
{
char *car_vendor; 		 // Марка а/м
char *car_model; 		// Модель а/м
int car_year; 			   // Год производства
char *car_id ; 			  // Номерной знак а/м
char *key;
int carrying; 	// Грузоподъемность (кг)
int axles;     // переднеприводная и задняприводная 6 на 4 - 4 ведущих 
  struct snode* ptr; // указатель на следующий элемент
}tnode;  
int push_back(char* vendor, char* model, int year, char* id, char* devise, int carry, int ax, tnode** node) {
	//calloc_os++;
	l++;
	tnode* temp;
	if (!(*node))
	{
		*node = calloc(1, sizeof(tnode)); //calloc_os++;
		(*node)->car_vendor = vendor;
		(*node)->car_model = model;
		(*node)->car_year = year;
		(*node)->key = devise;
		(*node)->car_id = id;
		(*node)->carrying = carry;
		(*node)->axles = ax;
	} //использование  указателя на неполный тип класса struct list не допускается
	else {
		temp = *node;
		while (temp->ptr != NULL) temp = temp->ptr;
		temp->ptr = calloc(1, sizeof(tnode)); //calloc_os++;
		temp->ptr->car_vendor = vendor;
		temp->ptr->car_model = model;
		temp->ptr->car_year = year; //printf(" %d ", k);
		temp->ptr->key = devise;
		temp->ptr->car_id = id;
		temp->ptr->carrying = carry;
		temp->ptr->axles = ax;
	}
	return 0;
}
void matr(int** y, int l, char *x, int i) {
	forenum(x); 
		for (int j = 0; j < 6; j++) {
			y[i][j] = know[j];
			//printf(" %d", know[j])
		}
		//printf("\n");
}
void search(tnode* lst, int axles, int carrying, int car_year, int* for_yy2, int* mas_for_dev, int* for_search, int* divise, int* counter, char* vendor, char* model, char* id,char* key) {
	select = 0;
	if (for_yy2[0] != 0) {
		tnode* p = lst;
		int i = 1, step =0; 
		while (p  != NULL ) {
			if (strcmp(vendor, p->car_vendor) == 0) {
				matritsa[i][0] = 0;
				//printf("%s\n", p->car_vendor);
				p = p->ptr;
				i++;
			}
			else {
				i++;
				p = p->ptr;
			}
			//printf("%d\n", i);
		}



	}
	if (for_yy2[1] != 0) {
		tnode* p = lst;
		int i = 1, step = 0;
		while (p != NULL) {
			if (strcmp(model, p->car_model) == 0) {
				matritsa[i][1] = 0;
				p = p->ptr;
				i++;
			}
			else {
				i++;
				p = p->ptr;
			}
		}
	}
	if (for_yy2[2] != 0) //car_year 
	{
		tnode* p = lst;
		int a = for_yy2[2]; //printf("a %d\n", a);
		int i = 0;
		switch (a) {

		case 1: //<
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {

				if (p->car_year >= car_year) {
					i++; q++;
				}
				if (p->car_year < car_year) {
					i++; q--;
					matritsa[i][2] = 0;
					}
			}
		}break;
		case 2: //>
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {
				if (p->car_year <= car_year) {
					i++; q++;
				}
				if (p->car_year > car_year) {
					i++; q--;
					matritsa[i][2] = 0;
				}
			}
		}break;

		case 8 : //==
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {

				if (p->car_year != car_year) {
					i++; q++;
				}
				if (p->car_year == car_year) {
					i++; q--;
					matritsa[i][2] = 0;
				}
			}
		}break;
		}

	}
	if (for_yy2[3] != 0) {
		tnode* p = lst;
		int i = 1, step = 0;
		while (p != NULL) {
			if (strcmp(id, p->car_id) == 0) {
				matritsa[i][3] = 0;
				p = p->ptr;
				i++;
			}
			else {
				i++;
				p = p->ptr;
			}
		}
	}
	if (for_yy2[4] != 0) //divise
	{
		int a = for_yy2[4];
		
		select++;
		if (select == 1) {
			l++;
			matritsa_dev = (int*)malloc(l * sizeof(int)); malloc_os++; free_os++;
			for (int s = 1; s < l; s++) // цикл по строкам
			{
				matritsa_dev[s] = (int*)malloc(6 * sizeof(int)); malloc_os++; free_os++;
				for (int j = 0; j < 6; j++)  // цикл по столбцам
				{
					matritsa_dev[s][j] = 0;
				}
			}
			
			tnode* p = lst; int i = 1;
			while (p != NULL) { 
				matr(matritsa_dev, l, p->key, i);
				p = p->ptr;
				i++;
			}
			l--;
		}
		
		
		switch (a) {
		case 3: //items include
		{
			int d = 0, n = 0, key = 0, flag = 0;
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) {
					if (divise[i] != 1) {
						printf("not correct ");
						break;
					}
				}
			}
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) key++;
			}
			
			while (d != -1) {
				d = lin_search(mas_for_dev);
				if (d != -1) {
					mas_for_dev[d] = 0; n = counter[d];
				}
				int q = 0;
				for (int i = 1; i < l; i++) {

					if (matritsa_dev[i][d] == 1) {
						matritsa_dev[i][d] = 2;
						q++;
					}
					if (q == n) break;
				}
			}
			
			for (int i = 1; i < l; ) {
				for (int j = 0; j < 6; j++) {
					if (matritsa_dev[i][j] == 2) flag++;
				}
				if (flag == key) matritsa[i][4] = 0;
				i++;
				flag = 0;
			}
		}break; //case 3 (items include);
		case 4: //status in
		{
			int a = 0;
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) {
					if (divise[i] != 1) {
						mas_for_dev[i] = -1;
					}
				}
				a += mas_for_dev[i];
				if(a < 0){
					printf("not correct");
					 break;
				}
			}
			int d = 0, n = 0;
			while (d != -1) {
				d = lin_search(mas_for_dev);
				if (d != -1) {
					mas_for_dev[d] = 0; n = counter[d];
				}
				int q = 0;
				for (int i = 1; i < l; i++) {
					if (matritsa_dev[i][d] == 1) {
						matritsa[i][4] = 0;
						q++;
					}
					if (q == n) break;
				}
			}
		} break; // status in
		case 5: //items==
		{

			int d = 0, n = 0, key = 0, flag = 0;
			for (int i = 0; i < 6; i++) {
				
				if (mas_for_dev[i] == 1) {
					if (divise[i] != 1) {
						printf("not correct ");
						break;
					}
				}
			}
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) key++;
			}
			
			while (d != -1) {
				d = lin_search(mas_for_dev);
				if (d != -1) {
					mas_for_dev[d] = 0; n = counter[d];
				}
				int q = 0;
				for (int i = 1; i < l; i++) {

					if (matritsa_dev[i][d] == 1) {
						matritsa_dev[i][d] = 2;
						q++;
					}
					if (q == n) break;
				}
			}
			
			for (int i = 1; i < l; ) {
				for (int j = 0; j < 6; j++) {
					if (matritsa_dev[i][j] == 2) flag++;
					if (matritsa_dev[i][j] == 1) flag--;
				}
				if (flag == key) matritsa[i][4] = 0;
				i++;
				flag = 0;
			}
			//if (um == 1) l--;
		}break; //items==
		case 6: //iteams!= 
		{

			int d = 0, n = 0, key = 0, flag = 0, prov = 0;
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) {
					if (divise[i] != 1) {
						printf("not correct ");
						break;
					}
				}
			}
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) key++;
			}
			while (d != -1) {
				d = lin_search(mas_for_dev);
				if (d != -1) {
					mas_for_dev[d] = 0; n = counter[d];
				}
				int q = 0;
				for (int i = 1; i < l; i++) {

					if (matritsa_dev[i][d] == 1) {
						matritsa_dev[i][d] = 2;
						q++;
					}
					if (q == n) break;
				}
			}
			for (int i = 1; i < l; ) {
				for (int j = 0; j < 6; j++) {
					if (matritsa_dev[i][j] == 2) flag++;
				}
				if (flag == 0) matritsa[i][4] = 0;
				
				flag = 0;
				i++;
			}
		}break; //iteams!=
		case 7: //items in
		{
			for (int i = 0; i < 6; i++) {
				if (mas_for_dev[i] == 1) {
					if (divise[i] != 1) {
						mas_for_dev[i] = -1;

					}
				}
			}
			int d = 0, n = 0;
			while (d != -1) {
				d = lin_search(mas_for_dev);
				if (d != -1) {
					mas_for_dev[d] = 0; 
				}
				for (int i = 1; i < l; i++) {

					if (matritsa_dev[i][d] == 1) {
						matritsa_dev[i][d] = 2;
						
					}
					
				}
			}
			for (int i = 1; i < l; ) {
				for (int j = 0; j < 6; j++) {
					if (matritsa_dev[i][j] == 2) matritsa[i][4] = 0;
				}
				i++;
			}
		}break; //items in
		}
		
		l++;
		for (int i = 1; i < l; i++) {
			free(matritsa_dev[i]);
			
		}
		free(matritsa_dev); 
		l--;
    }
	if (for_yy2[5] != 0) // carryinf
	{
		tnode* p = lst;
		int a = for_yy2[5]; //printf("a %d\n", a);
		int i = 0;
		switch (a) {
		case 1: //<
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {
				if (p->carrying >= carrying) {
					i++; q++;
				}
				if (p->carrying < carrying) {
					i++; q--;
					matritsa[i][5] = 0;
				}
			}
		}break;

		case 2: //>
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {
				if (p->carrying <= carrying) {
					i++; q++;
				}
				if (p->carrying > carrying) {
					i++; q--;
					matritsa[i][5] = 0;
				}
			}
		}break;

		case 8 :
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {
				if (p->carrying != carrying) {
					i++; q++;
				}
				if (p->carrying == carrying) {
					i++; q--;
					matritsa[i][5] = 0;
				}
			}
		}break;
		}
	}
	if (for_yy2[6] != 0) //axless
	{
		tnode* p = lst;
		int a = for_yy2[6]; //printf("a %d\n", a);
		int i = 0;
		switch (a) {

		case 1: //<
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {
				if (p->axles >= axles) {
					i++; q++;
				}
				if (p->axles < axles) {
					i++; q--;
					matritsa[i][6] = 0;
					//printf("%, d ", p->car_year);

				}


			}
		}break;

		case 2: //>
		{
			int q = 0;
			for (; p != NULL; p = p->ptr) {

				if (p->axles <= axles) {
					i++; q++;
				}
				if (p->axles > axles) {
					i++; q--;
					matritsa[i][6] = 0;
				}
			}
		}break;
		case 8: 
		{

			int q = 0;
			for (; p != NULL; p = p->ptr) {
				if (p->axles != axles) {
					i++; q++;
				}
				if (p->axles == axles) {
					i++; q--;
					matritsa[i][6] = 0;
					//printf("%, d ", p->car_year);

				}


			}
		}break;
		}
	}	
}
tnode* Mdelete(tnode* node, int s, int i ) {
	//free_os++;
	//printf("%s", prev->car_vendor);
//	l--;
	if (i == s)s = 1;
	switch (s) {
	case 1: {

		tnode* p=node;
		p = node->ptr;
		free(node); free_v1++;
		//printf("%s", p->car_vendor);
		return (p);
	}break;
	default: {
			tnode* p = node; tnode* prev = node;
			
			for (; i < s; i++) {
				prev = p;
				p = p->ptr;
			}

			prev->ptr = p->ptr;
			free(p); free_v1++;
			return node;
		}break;
	}
	}
tnode* for_delet(tnode* list, int deletee, int *y) {
	

	int* delet_help = (int*)calloc(l, sizeof(int)); calloc_os++;
	int s = 0;
	for (int j = 1; j < l; j++) {
		if (matritsa[j][0] == 0) delet_help[j] = 1;
		//printf("%d ", delet_help[j]);
	}

	int q = 1;
	if (deletee >= 1) {
		while (q <= deletee) {
			s = lin_search_ver(delet_help);
			if (s != -1) {
				delet_help[s] = 0;
				//if (q > 0) s--;
				list = Mdelete(list, s, q);
				//free_v1++; //free_os++;
				q++;

			}
			if (s == -1) break;
		}
		
		
		free(delet_help); free_os++;
		/*tnode* t = list;
		while (t != NULL) {
			printf("%s %s %s\n", t->car_vendor, t->car_model, t->car_id);
			t = t->ptr;
		}*/
		return list;
		
	}

}
tnode* remove_all(tnode* head)
{
	
	while (head != NULL)
	{
		
		tnode* p = head;
		
		head = head->ptr;
		free_v1++;
		free(p); //free_os++;
	}
	return NULL;
}

int main() {
	int malloc_v1 = 0, calloc_v1 = 0,  realloc_v1 = 0;
	int malloc_v2 = 0, calloc_v2 = 0, free_v2 = 0, realloc_v2 = 0;
	int malloc_v3 = 0, calloc_v3 = 0, free_v3 = 0, realloc_v3 = 0;
	int malloc_v4 = 0, calloc_v4 = 0, free_v4 = 0, realloc_v4 = 0;
	int malloc_v5 = 0, calloc_v5 = 0, free_v5 = 0, realloc_v5 = 0;

	tnode* list = NULL; 
	FILE* in, * out;
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	char qwer = EOF, next = EOF; int func = 0;
	int devise[6] = { 0 }, counter[6] = { 0 };
	int count = 0, delete = 0, kt = 0,kt_v4=0;
	while (1) {
		char y[15] = { 0 }; //for (int q = 0; q < 15; q++) y[q] = 0;
		fscanf(in, "%s", y); //printf("%s\n", y);
		int x = f_proverka(y); //printf("x %d ", x);
		switch (x) 
		{ 
		  case 1 :   //insert
		  {
			 
			  func++;
			  int mas_proverka[7] = { 0 };
			  char name_of_func[22] = { 0 };
			  int car_year = 0, carrying = 0, axles = 0;
			  char* car_vendor = 0, * car_model = 0, * car_id = 0, * devise_for = 0;
			  char prev = 0, next = 0;
			  int step = 0;
			  while (step != 7) {
				  for (int i = 0; i < 22; i++) name_of_func[i] = 0;
				  int i = 0;
				  while (1) {
					  prev = fgetc(in);
					  if (prev != ' ') {
						  name_of_func[i] = prev;
						  if (i == 22) break; i++;
						  if (prev == '=') break;
					  }
				  }
				  //  for (int i = 0; i < 22; i++) printf("%c ", name_of_func[i]);
				  int flag = insert_proverka(name_of_func); //printf("%d\n", flag);
				  switch (flag) {
				  case 1: //марка
				  {
					  if (mas_proverka[0] == 0) {
						  char name_car_vendor[15] = { 0 }; fscanf(in, "%s", name_car_vendor);
						  // printf("%s", name_car_vendor);
						  int k = strlen(name_car_vendor) - 1;
						  car_vendor = (char*)calloc(k + 1, sizeof(char)); calloc_v1++;
						  for (int i = 0, q = 0; (i < k) || (q < k); q++) {
							  if (name_car_vendor[i] == ',') break;
							  car_vendor[q] = name_car_vendor[i]; i++;
							  //printf("%c", car_vendor[q]);
						  }
						  step++;
						  mas_proverka[0] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  } 
				  }break;
				  case 2:  //модель
				  {
					  if (mas_proverka[1] == 0) {
						  char name_model[15] = { 0 };
						  fscanf(in, "%s", name_model); //printf("%s", name_model);
						  int  k = strlen(name_of_func) - 1;
						  car_model = (char*)calloc(k + 1, sizeof(char)); calloc_v1++;
						  for (int i = 0, q = 0; (i < k) || (q < k); q++) {
							  if (name_model[i] == ',') break;
							  car_model[q] = name_model[i]; i++;
						  }
						  step++;
						  mas_proverka[1] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }  
				  }break;
				  case 3: //год
				  {
					  if (mas_proverka[2] == 0) {
						  fscanf(in, "%d", &car_year);
						  while (1) {
							  prev = fgetc(in);
							  if (prev == ',') break;

						  }
						  mas_proverka[2] = 1;
						  step++;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
					  
				  }break;
				  case 4: //нмоерной знак
				  {
					  if (mas_proverka[3] == 0) {
						  char name_id[15] = { 0 }; fscanf(in, "%s", name_id);
						  int k = strlen(name_of_func) - 1;
						  car_id = (char*)calloc(k + 1, sizeof(char)); calloc_v1++;
						  for (int i = 0, q = 0; (i < k) || (q < k); q++) {
							  if (name_of_func[i] == ',') break;
							  car_id[q] = name_id[i]; i++;
						  }
						  mas_proverka[3] = 1;
						  step++;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 5: //дивайсы
				  {
					  if (mas_proverka[4] == 0) {
						  int  k = -1; int j = 0, jj = 0; char devise_st[40] = { 0 }; char dev[12] = { 0 };
						  int coma = 0; char q = 0;
						  fscanf(in, "%s", devise_st); //printf("%s", devise_st);
						  jj = strlen(devise_st);
						  next = fgetc(in);
						  q = next;
						  devise_st[jj] = q;

						  for (int i = 0; i <= jj; i++) {
							  if (devise_st[i] == ',') {
								  k = proverka(dev);
								  if (k == -1) { printf("not true"); break; }
								  devise[k] = 1; j = 0;
								  for (int s = 0; s < 12; s++) dev[s] = 0;
								  switch (k) {
								  case 0: counter[0]++; break;
								  case 1: counter[1]++; break;
								  case 2: counter[2]++; break;
								  case 3: counter[3]++; break;
								  case 4: counter[4]++; break;
								  case 5: counter[5]++; break;
								  }
							  }
							  if (devise_st[i] == ' ') {

								  k = proverka(dev);
								  if (k == -1) { printf("not true"); break; }
								  devise[k] = 1;
								  switch (k) {
								  case 0: counter[0]++; break;
								  case 1: counter[1]++; break;
								  case 2: counter[2]++; break;
								  case 3: counter[3]++; break;
								  case 4: counter[4]++; break;
								  case 5: counter[5]++; break;
								  }

								  i = jj;
								  break;
							  }
							  if (devise_st[i] != '\'' && devise_st[i] != ',') {
								  dev[j] = devise_st[i];
								  j++;
							  }
						  }
						  devise_st[jj] = '\0';
						  devise_for = (char*)calloc(jj + 1, sizeof(char)); calloc_v1++;
						  for (int i = 0, q = 0; (i < jj) || (q < jj); q++) {
							  devise_for[q] = devise_st[i]; i++;
							  //printf("%c\n", devise_for[q]);
						  }
						  mas_proverka[4] = 1;
						  step++;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }  
				  }break;
				  case 6:
				  {
					  if (mas_proverka[5] == 0) {
						  fscanf(in, "%d", &carrying);
						  while (1) {
							  prev = fgetc(in);
							  if (prev == ',') break;
						  }
						  mas_proverka[5] = 1;
						  step++;
					  } 
					  else {
						  printf("not correct");
						  return 500;
					  }
					  
				  }break;
				  case 7:
				  {
					  if (mas_proverka[6] == 0) {
						  fscanf(in, "%d", &axles);
						  mas_proverka[6] = 1;
						  step++;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case -1:
				  {
					  printf("not correct");
					  return -2;
				  }break;
				  }
			  }
			  
			  push_back(car_vendor, car_model, car_year, car_id, devise_for, carrying, axles, &list);
			 
			  
			  // free(car_vendor); free_v1++;
			 // free(car_model); free_v1++;
			  //free(car_id); free_v1++;
			  //free(devise_for); free_v1++;
		  }break; // case1
		 
		  case 2 : //selekt  
		  {
			   char  prev = 0, next =0;
			   char yy[59] = { 0 }, t[7] = { ',' }; int flag = 0;
			   char yy2[80] = { 0 }; int for_yy2[7] = { 0 }; char dev[12] = { 0 }; int mas_for_dev[6] = { 0 };
			   int axles_case = 0, carrying_case = 0, car_year_case = 0, cover = 0; int for_search[7] = { 0 }, save_l = 0, l_prev = 0;
			   fscanf(in, "%s", yy);  
			  prev = fgetc(in);// printf("%d\n", prev);
			 int we = 0;
			 int w = 1;
			 if (prev != '\n') //ВВОД ДОПОВ
			 {
				 cover = 1;
				 while (w != -1) {
					 switch (w)
					 {

					 case 1:
					 {
						 while (1) {
							 next = prev;
							 prev = fgetc(in);

							 if ((prev == '=') || (prev == '\n') || (prev == '/') || (prev == '>') || (prev == '<') || (next == '=' && prev == '=') || (next == '!' && prev == '=') || (next == '=' && prev == '!') || prev == '!') break;
							 if (prev != ' ') {
								 yy2[we] = prev;
								 if (we == 10) break; 
								 we++;

							 }
						 }
						 }break;
					 }

					 int k = proverka_yes(yy2);
					 if (k == -1) {
						 int q = 0;
						 for (int i = 0; i < 80; i++) {
							 q += yy2[i];
							 if (q != 0)
								 printf("yy2: not true"); break;
						 }
					 }//printf("K_%d\n ", k);
					 for (int o = 0; o < 80; o++) yy2[o] = 0; we = 0;
					 if (prev == '<') {
						 for_yy2[k - 1] = 1;
						 if (k == 7) fscanf(in, "%d", &axles_case);
						 if (k == 6) fscanf(in, "%d", &carrying_case);
						 if (k == 3) fscanf(in, "%d", &car_year_case);
						 // printf("%d ", for_yy2[k - 1]);
					 }
					 if (prev == '>') {
						 for_yy2[k - 1] = 2;
						 if (k == 7) fscanf(in, "%d", &axles_case);
						 if (k == 6) fscanf(in, "%d", &carrying_case);
						 if (k == 3) fscanf(in, "%d", &car_year_case);

						 // printf("%d ", for_yy2[k - 1]);
					 }
					 if (prev == '/') {
						 int wwe = 0;
						 while (wwe < 7) {
							 next = fgetc(in);
							 if (next == '/' || next == '=' || next == '!') break;
							 dev[wwe] = next;
							// printf("%c\n", dev[wwe]);
							 wwe++;
						 }
						 int kk = proverka_yes(dev); //printf("\nstat %d\n", kk);
						 for (int o = 0; o < wwe; o++) dev[o] = 0;
						 if (kk == 10) //items
						 {
							 //printf("%c\n", next);
							 if (next == '/') {
								 wwe = 0;
								 while (wwe < 7) {
									 next = fgetc(in);
									 if (next == '/' || next == '=' || next == '\'') break;
									 dev[wwe] = next;
									 //printf("--%c\n", next);
									 wwe++;

								 }
								 kk = proverka_yes(dev);  //printf(" %d\n", kk);

								 for (int o = 0; o < wwe; o++) dev[o] = 0;//printf("\nstat %d\n", kk);
								 if (kk == 8) { //include
									 for_yy2[k - 1] = 3;
									 wwe = 0;
									 while (1) {
										 next = fgetc(in);
										 if (next == ',') {
											 kk = proverka(dev); // printf(" \n 2-%d ", kk);
											 if (kk == -1) { printf("not true"); break; }
											 mas_for_dev[kk] = 1; wwe = 0;
											 for (int o = 0; o < 12; o++) dev[o] = 0;

										 }
										 if (next == ']') {
											 kk = proverka(dev);  //printf(" \n 2-%d ", kk);
											 if (kk == -1) { printf("not true"); break; }
											 mas_for_dev[kk] = 1;
											 break;
										 }
										 if (next != '\'' && next != '[' && next != ',' && next != '/') {
											 dev[wwe] = next;
											 /*printf(" %c ", dev[wwe]);*/ wwe++;
										 }
									 }
									 //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
								 }
								 if (kk == 9) { // in 
									 for_yy2[k - 1] = 7;
									 wwe = 0;
									 while (1) {
										 next = fgetc(in);
										 if (next == ',') {
											 kk = proverka(dev);
											 if (kk == -1) { printf("kk not true\n"); break; }//printf(" \n 2-%d ", kk);
											 mas_for_dev[kk] = 1; wwe = 0;
											 for (int o = 0; o < 12; o++) dev[o] = 0;

										 }
										 if (next == ']') {
											 kk = proverka(dev);
											 if (kk == -1) { printf("kk not true"); break; }//printf(" \n 2-%d ", kk);
											 mas_for_dev[kk] = 1;
											 break;
										 }
										 if (next != '\'' && next != '[' && next != ',') {
											 dev[wwe] = next;
											 // printf("in  %c\n", dev[wwe]); 
											 wwe++;
										 }
									 }
									 //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
								 }
								 if (kk == -1) { printf("not correct"); return -1;; }
							 }
							 else {
								 // prev = fgetc(in); printf("prev %c", prev);
								 if (next == '=') {
									 prev = fgetc(in); //printf("next %c\n", prev);
									 if (prev == '=') {
										 for_yy2[k - 1] = 5;
										 int kk = 0, wwe = 0;
										 while (1)
										 {
											 next = fgetc(in);
											 if (next == ',') {
												 kk = proverka(dev); // printf(" \n 2-%d ", kk);
												 if (kk == -1) { printf("not true"); break; }
												 mas_for_dev[kk] = 1; wwe = 0;
												 for (int o = 0; o < 12; o++) dev[o] = 0;

											 }
											 if (next == ']') {
												 kk = proverka(dev);  //printf(" \n 2-%d ", kk);
												 if (kk == -1) { printf("not true"); break; }
												 mas_for_dev[kk] = 1;
												 break;
											 }
											 if (next != '\'' && next != '[' && next != ',' && next != '/') {
												 dev[wwe] = next;
												 //printf("C %c\n", dev[wwe]);
												 wwe++;
											 }
										 }

									 }
									 else { printf("items==: not true"); return -1; }
									 //printf("%d ", for_yy2[k - 1]);
								 }
								 if (next == '!') {
									 prev = fgetc(in);
									 if (prev == '=')
									 {
										 for_yy2[k - 1] = 6;
										 int kk = 0, wwe = 0;
										 while (1) {
											 next = fgetc(in);
											 if (next == ',') {
												 kk = proverka(dev); // printf(" \n 2-%d ", kk);
												 if (kk == -1) { printf("not true"); break; }
												 mas_for_dev[kk] = 1; wwe = 0;
												 for (int o = 0; o < 12; o++) dev[o] = 0;

											 }
											 if (next == ']') {
												 kk = proverka(dev);  //printf(" \n 2-%d ", kk);
												 if (kk == -1) { printf("not true"); break; }
												 mas_for_dev[kk] = 1;
												 break;
											 }
											 if (next != '\'' && next != '[' && next != ',' && next != '/') {
												 dev[wwe] = next;
												 // printf("C %c\n", dev[wwe]);
												 wwe++;
											 }

										 }
										 // for (int o = 0; o < 6; o++) printf("%d\n", mas_for_dev[o]);
									 }
									 else { printf("not true!="); return -1; }
								 }
							 }
						 }
						 if (kk == 11) //status
						 {
							  wwe = 0;
							 while (wwe < 7) {
								 next = fgetc(in);
								 if (next == '/') break;
								 dev[wwe] = next;
								 //printf("%c\n", dev[wwe]);
								 wwe++;
							 }
							  kk = proverka_yes(dev); //printf("\nstat %d\n", kk);
							  for (int o = 0; o < wwe; o++) dev[o] = 0;
							  if (kk == 9) { // in 
								  for_yy2[k - 1] = 4;
								  wwe = 0;
								  while (1) {
									  next = fgetc(in);
									  if (next == ',') {
										  kk = proverka(dev);
										  if (kk == -1) { printf("kk not true\n"); break; }//printf(" \n 2-%d ", kk);
										  mas_for_dev[kk] = 1; wwe = 0;
										  for (int o = 0; o < 12; o++) dev[o] = 0;

									  }
									  if (next == ']') {
										  kk = proverka(dev);
										  if (kk == -1) { printf("kk not true"); break; }//printf(" \n 2-%d ", kk);
										  mas_for_dev[kk] = 1;
										  break;
									  }
									  if (next != '\'' && next != '[' && next != ',') {
										  dev[wwe] = next;
										  // printf("in  %c\n", dev[wwe]); 
										  wwe++;
									  }
								  }
								  //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
						 }

						 
					 }
					 }
					 if (prev == '\n') w = -1;
					 if (prev == ' ') w = 1;
				 }
             }
			 int y = 0, a = 0; int zapisi = 0;
			 
			
			 if (cover == 1) {
				 tnode* p = list; int lll = 1;
				 while (p != NULL) {
					 lll++;
					 p = p->ptr;
				 }
				 l = lll;
					  matritsa = (int**)malloc((l) * sizeof(int*)); malloc_v2++;
					 for (int i = 1; i < (l); i++) {
						 matritsa[i] = (int*)malloc(7 * sizeof(int)); malloc_v2++;
						// printf("%d: ", i);
						 for (int j = 0; j < 7; j++) {
							 matritsa[i][j] = -1;
							
							 //printf("%d ", matritsa[i][j]);
						 }
						 //printf("\n");
					 }

					 for (int i = 0; i < 7; i++) {
						 if (for_yy2[i] != 0) {
							 for (int y = 1; y < l; y++)  matritsa[y][i] = 1;
						 }
					 }
					 l--;
					
				search(list, axles_case, carrying_case, car_year_case, for_yy2, mas_for_dev, for_search,devise, counter,0,0,0,0);
				

				for (int i = 1; i < l; i++) {
					 for (int j = 0; j < 7; j++) {
						 if (matritsa[i][j] == 1) {
							 for (int z = 0; z < 7; z++) matritsa[i][z] = 1;
						 }
					 }
					 if ( matritsa[i][0] != 1)
					 {
						 if (matritsa[i][1] != 1) {
							 if (matritsa[i][2] != 1) {
								 if (matritsa[i][3] != 1) {
									 if (matritsa[i][4] != 1) {
										 if (matritsa[i][5] != 1) {
											 if (matritsa[i][6] != 1) zapisi++;
										 }
									 }

								 }
							 }
						}
					 }
				 }
				
				printf("select:%d\n", zapisi+1);
			 }
			 if (cover == 0) {
				 tnode* p = list; int lll = 1;
				 while (p != NULL) {
					 lll++;
					 p = p->ptr;
				 }
				 l = lll;
				// l++;
				 matritsa = (int**)malloc((l) * sizeof(int*)); malloc_v2++;
				 for (int i = 1; i < (l); i++) {
					 matritsa[i] = (int*)malloc(7 * sizeof(int)); malloc_v2++;
					 // printf("%d: ", i);
					 for (int j = 0; j < 7; j++) {
						 matritsa[i][j] = -1;

						 //printf("%d ", matritsa[i][j]);
					 }
					 //printf("\n");
				 }
				 save_l = l;
				 l--;
				 qwer++;
			 }
				 for (int i = 0; i < 59; i++) {
					 if (yy[i] == ',') flag++;
				 }
				 flag++;
				 int* mass_for = calloc(flag, sizeof(int)); calloc_v2++;
				 char* q = strtok(yy, t);
				 int x2 = 0;
				 int i = 0;
				 while (q != NULL && i < flag) {
					 mass_for[i] = proverka_yes(q); i++;
					 q = strtok(NULL, t);
				 }
				 tnode* p = list;
				 int ii = 0;int b = 1,printf_n = 0, swirch_n=0;
				 printf_n = mass_for[flag - 1];
				
				 if (l > 0) {
					 while (p != NULL)
					 {
						 if (ii == flag) {
							 ii = 0;
							 p = p->ptr;
							 // printf("\n");
							 if (swirch_n == printf_n) printf("\n");
							 swirch_n = 0;
							 if (p == NULL) break;
							 b++;
							 if (b > l)break;
						 }
						 int x2 = mass_for[ii];
						 switch (x2)
						 {

						 case 1:
						 {
							 if (matritsa[b][0] != 1) {
								 printf("car_vendor:%s ", p->car_vendor);
								 swirch_n = 1;
							 }
						 } break;
						 case 2:
						 {
							 if (matritsa[b][1] != 1) {
								 printf(" car_model:%s ", p->car_model);
								 swirch_n = 2;
							 }
						 }break;
						 case 3:
						 {
							 if (matritsa[b][2] != 1) {

								 printf("car_year:%d ", p->car_year);
								 swirch_n = 3;

							 }

						 }break;
						 case 4:
						 {
							 if (matritsa[b][4] != 1) {
								 printf("divise:%s ", p->key); //printf("matr: ",i, matritsa[i][3]);
								 swirch_n = 4;
							 }
						 }break;
						 case 5:
						 {
							 if (matritsa[b][3] != 1) {
								 printf("id:%s ", p->car_id);
								 swirch_n = 5;
							 }
						 }break;
						 case 6: {
							 if (matritsa[b][5] != 1) {
								 printf("carrying:%d ", p->carrying);
								 swirch_n = 6;
							 }
						 }break;
						 case 7:
						 {
							 if (matritsa[b][6] != 1) {
								 printf("axles:%d", p->axles);
								 swirch_n = 7;
							 }
						 }break;
						 }

						 ii++;
					 }
				 }
				 else printf("lis is empty");
				 if (cover == 1) {
					 l++;
					 for (int i = 1; i < l; i++) {
						 free(matritsa[i]); free_v2++;

					 }
					 free(matritsa);  free_v2++;
					 free(mass_for); free_v2++;
					 l--;
				 }
				 if (cover == 0) {
					 l_prev = l;
					 l = save_l;
					 for (int i = 1; i < l; i++) {
						 free(matritsa[i]); free_v2++;

					 }
					 free(matritsa);  free_v2++;
					 free(mass_for); free_v2++;
					 l = l_prev;
				 }

		  }break; //case 2 
		
		  case 3: //delete 
		  {
			  kt++;
			  int delete=0;
			  char  prev = 0, next = 0;
			  char yy2[80] = { 0 }; int for_yy2[7] = { 0 }; int for_yy2_case[7] = { 0 }; char dev[12] = { 0 }; int mas_for_dev[6] = { 0 };
			  int axles_case = 0, carrying_case = 0, car_year_case = 0, cover = 0; int for_search[7] = { 0 };
			  char* vendor=0, * model=0, * id=0; char name_of_word[15] = { 0 };
			  prev = fgetc(in);
			  int we = 0; int w = 1;
			  while (w != -1) {
				  switch (w)
				  {

				  case 1:
				  {
					  while (1) {
						  next = prev;
						  prev = fgetc(in);

						  if ((prev == '=') || (prev == '\n') || (prev == '/') || (prev == '>') || (prev == '<') || (next == '=' && prev == '=') || (next == '!' && prev == '=') || (next == '=' && prev == '!') || prev == '!') break;
						  if (prev != ' ') {
							  yy2[we] = prev;
							  if (we == 10) break;
							  we++;

						  }
					  }
				  }break;
				  }

				  int k = proverka_yes(yy2);
				  if (k == -1) {
					  int q = 0;
					  for (int i = 0; i < 80; i++) {
						  q += yy2[i];
						  if (q != 0)
							  printf("yy2: not true"); break;
					  }
				  }//printf("K_%d\n ", k);
				  for (int o = 0; o < 80; o++) yy2[o] = 0; we = 0;
				  if (prev == '<') {
					  for_yy2[k - 1] = 1;
					  if (k == 7) fscanf(in, "%d", &axles_case);
					  if (k == 6) fscanf(in, "%d", &carrying_case);
					  if (k == 3) fscanf(in, "%d", &car_year_case);
					  // printf("%d ", for_yy2[k - 1]);
				  }
				  if (prev == '>') {
					  for_yy2[k - 1] = 2;
					  if (k == 7) fscanf(in, "%d", &axles_case);
					  if (k == 6) fscanf(in, "%d", &carrying_case);
					  if (k == 3) fscanf(in, "%d", &car_year_case);

					  // printf("%d ", for_yy2[k - 1]);
				  }
				  if (prev == '/') {
					  int wwe = 0;
					  while (wwe < 7) {
						  next = fgetc(in);
						  if (next == '/' || next == '=' || next == '!') break;
						  dev[wwe] = next;
						  // printf("%c\n", dev[wwe]);
						  wwe++;
					  }
					  int kk = proverka_yes(dev); //printf("\nstat %d\n", kk);
					  for (int o = 0; o < wwe; o++) dev[o] = 0;
					  if (kk == 10) //items
					  {
						  //printf("%c\n", next);
						  if (next == '/') {
							  wwe = 0;
							  while (wwe < 7) {
								  next = fgetc(in);
								  if (next == '/' || next == '=' || next == '\'') break;
								  dev[wwe] = next;
								  //printf("--%c\n", next);
								  wwe++;

							  }
							  kk = proverka_yes(dev);  //printf(" %d\n", kk);

							  for (int o = 0; o < wwe; o++) dev[o] = 0;//printf("\nstat %d\n", kk);
							  if (kk == 8) { //include
								  for_yy2[k - 1] = 3;
								  wwe = 0;
								  while (1) {
									  next = fgetc(in);
									  if (next == ',') {
										  kk = proverka(dev); // printf(" \n 2-%d ", kk);
										  if (kk == -1) { printf("not true"); break; }
										  mas_for_dev[kk] = 1; wwe = 0;
										  for (int o = 0; o < 12; o++) dev[o] = 0;

									  }
									  if (next == ']') {
										  kk = proverka(dev);  //printf(" \n 2-%d ", kk);
										  if (kk == -1) { printf("not true"); break; }
										  mas_for_dev[kk] = 1;
										  break;
									  }
									  if (next != '\'' && next != '[' && next != ',' && next != '/') {
										  dev[wwe] = next;
										  /*printf(" %c ", dev[wwe]);*/ wwe++;
									  }
								  }
								  //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
							  }
							  if (kk == 9) { // in 
								  for_yy2[k - 1] = 7;
								  wwe = 0;
								  while (1) {
									  next = fgetc(in);
									  if (next == ',') {
										  kk = proverka(dev);
										  if (kk == -1) { printf("kk not true\n"); break; }//printf(" \n 2-%d ", kk);
										  mas_for_dev[kk] = 1; wwe = 0;
										  for (int o = 0; o < 12; o++) dev[o] = 0;

									  }
									  if (next == ']') {
										  kk = proverka(dev);
										  if (kk == -1) { printf("kk not true"); break; }//printf(" \n 2-%d ", kk);
										  mas_for_dev[kk] = 1;
										  break;
									  }
									  if (next != '\'' && next != '[' && next != ',') {
										  dev[wwe] = next;
										  // printf("in  %c\n", dev[wwe]); 
										  wwe++;
									  }
								  }
								  //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
							  }
							  if (kk == -1) { printf("not correct"); return -1;; }
						  }
						  else {
							  // prev = fgetc(in); printf("prev %c", prev);
							  if (next == '=') {
								  prev = fgetc(in); //printf("next %c\n", prev);
								  if (prev == '=') {
									  for_yy2[k - 1] = 5;
									  int kk = 0, wwe = 0;
									  while (1)
									  {
										  next = fgetc(in);
										  if (next == ',') {
											  kk = proverka(dev); // printf(" \n 2-%d ", kk);
											  if (kk == -1) { printf("not true"); break; }
											  mas_for_dev[kk] = 1; wwe = 0;
											  for (int o = 0; o < 12; o++) dev[o] = 0;

										  }
										  if (next == ']') {
											  kk = proverka(dev);  //printf(" \n 2-%d ", kk);
											  if (kk == -1) { printf("not true"); break; }
											  mas_for_dev[kk] = 1;
											  break;
										  }
										  if (next != '\'' && next != '[' && next != ',' && next != '/') {
											  dev[wwe] = next;
											  //printf("C %c\n", dev[wwe]);
											  wwe++;
										  }
									  }

								  }
								  else { printf("items==: not true"); return -1; }
								  //printf("%d ", for_yy2[k - 1]);
							  }
							  if (next == '!') {
								  prev = fgetc(in);
								  if (prev == '=')
								  {
									  for_yy2[k - 1] = 6;
									  int kk = 0, wwe = 0;
									  while (1) {
										  next = fgetc(in);
										  if (next == ',') {
											  kk = proverka(dev); // printf(" \n 2-%d ", kk);
											  if (kk == -1) { printf("not true"); break; }
											  mas_for_dev[kk] = 1; wwe = 0;
											  for (int o = 0; o < 12; o++) dev[o] = 0;

										  }
										  if (next == ']') {
											  kk = proverka(dev);  //printf(" \n 2-%d ", kk);
											  if (kk == -1) { printf("not true"); break; }
											  mas_for_dev[kk] = 1;
											  break;
										  }
										  if (next != '\'' && next != '[' && next != ',' && next != '/') {
											  dev[wwe] = next;
											  // printf("C %c\n", dev[wwe]);
											  wwe++;
										  }

									  }
									  // for (int o = 0; o < 6; o++) printf("%d\n", mas_for_dev[o]);
								  }
								  else { printf("not true!="); return -1; }
							  }
						  }
					  }
					  if (kk == 11) //status
					  {
						  wwe = 0;
						  while (wwe < 7) {
							  next = fgetc(in);
							  if (next == '/') break;
							  dev[wwe] = next;
							  //printf("%c\n", dev[wwe]);
							  wwe++;
						  }
						  kk = proverka_yes(dev); //printf("\nstat %d\n", kk);
						  for (int o = 0; o < wwe; o++) dev[o] = 0;
						  if (kk == 9) { // in 
							  for_yy2[k - 1] = 4;
							  wwe = 0;
							  while (1) {
								  next = fgetc(in);
								  if (next == ',') {
									  kk = proverka(dev);
									  if (kk == -1) { printf("kk not true\n"); break; }//printf(" \n 2-%d ", kk);
									  mas_for_dev[kk] = 1; wwe = 0;
									  for (int o = 0; o < 12; o++) dev[o] = 0;

								  }
								  if (next == ']') {
									  kk = proverka(dev);
									  if (kk == -1) { printf("kk not true"); break; }//printf(" \n 2-%d ", kk);
									  mas_for_dev[kk] = 1;
									  break;
								  }
								  if (next != '\'' && next != '[' && next != ',') {
									  dev[wwe] = next;
									  // printf("in  %c\n", dev[wwe]); 
									  wwe++;
								  }
							  }
							  //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
						  }


					  }
				  }
				  if (prev == '\n') w = -1;
				  if (prev == ' ') w = 1;
				  if (prev == '=') {
						  prev = fgetc(in);
						  if (prev == '=') {
							 calloc_v3++;
							  for_yy2_case[k - 1] = 1;
							  if (k == 1) {
								  for_yy2[k-1] = 8;
								  fscanf(in, "%s", name_of_word);
								  int len = strlen(name_of_word) + 1;
								  vendor = (char*)calloc(len, sizeof(char)); 
								  for (int i = 0; i < len; i++) vendor[i] = name_of_word[i];
								 // printf("\n%s\n", vendor);
							  }
							  if (k == 2) {
								  for_yy2[k - 1] = 8;
								  fscanf(in, "%s", name_of_word);
								  int len = strlen(name_of_word) + 1;
								  model = (char*)calloc(len, sizeof(char));
								  for (int i = 0; i < len; i++) model[i] = name_of_word[i];
							  }
							  if (k == 3) {
								  for_yy2[k - 1] = 8;
								  fscanf(in, "%s", name_of_word);
								  int len = strlen(name_of_word) + 1;
								  id = (char*)calloc(len, sizeof(char)); 
								  for (int i = 0; i < len; i++) id[i] = name_of_word[i];
							  }
						  
						  }
						  
				  }
                 


              }
			  int l_save = 0, l_p = 0;;
			  
			 // printf("%d\n", l_save);
			  tnode* p = list; int lll = 1;
			  while (p != NULL) {
				  lll++;
				  p = p->ptr;
			  }
			  l = lll;
			  //l++;
			  l_save = l;
			  matritsa = (int**)malloc((l) * sizeof(int*)); 
			  malloc_v3++;
			  for (int i = 1; i < (l); i++) {
				  matritsa[i] = (int*)malloc(7 * sizeof(int));  
				  malloc_v3++;
				  // printf("%d: ", i);
				  for (int j = 0; j < 7; j++) {
					  matritsa[i][j] = -1;
					  //printf("%d ", matritsa[i][j]);
				  }
				  //printf("\n");
			  }

			  for (int i = 0; i < 7; i++) {
				  if (for_yy2[i] != 0) {
					  for (int y = 1; y < l; y++)  matritsa[y][i] = 1;
				  }
			  }
			  l--;
			  
			 /* tnode* p = list; int lll = 0;
			  while (p != NULL) {
				  lll++;
				  p = p->ptr;
			  }
			  l = lll+1;*/
			  search(list, axles_case, carrying_case, car_year_case, for_yy2, mas_for_dev, for_search, devise, counter,vendor,model,id,0);
			  

			/*  for (int s = 1; s < l; s++) {
				  for (int j = 0; j < 7; j++) {
					  printf("%d", matritsa[s][j]);
				  }
				  printf("\n");
			  }*/
			 
			  for (int s = 1; s < l;  s++) {
				  for (int j = 0; j < 7; j++) {
					  if (matritsa[s][j] == 1) {
						  for (int u = 0; u < 7; u++) matritsa[s][u] = 1;
					  }
					 
				  }
				  
				  if (matritsa[s][0] != 1)
				  {
					  if (matritsa[s][1] != 1) {
						  if (matritsa[s][2] != 1) {
							  if (matritsa[s][3] != 1) {
								  if (matritsa[s][4] != 1) {
									  if (matritsa[s][5] != 1) {
										  if (matritsa[s][6] != 1) delete++;
									  }
								  }

							  }
						  }
					  }
				  }
			  }
			  for (int s = 1; s < l; s++) {
				  for (int j = 0; j < 7; j++) {
					  if (matritsa[s][j] == 0) {
						  for (int u = 0; u < 7; u++) matritsa[s][u] = 0;
					  }
				  }
			  }
			  
			 
			  int* delet_help = (int*)calloc(l, sizeof(int)); calloc_v3++;
			  int s = 0;
				  for (int j = 1; j < l; j++) {
					  if (matritsa[j][1] == 0) {
						  delet_help[j] = 1;
					  }
				  }
				  int q = 1;
				  delete++;
				  while (q < delete) {
					  s = lin_search_ver(delet_help);

					  if (s != -1) { 
						  delet_help[s] = 0;
						  //if (q > 0) s--;
						  list = Mdelete(list, s,q);
						  q++;

					  }
					  if (s == -1) break;
				  }
				  delete--;
				 
				 printf("delete: %d\n", delete);
				// if (kt > 1) l++;
				 l++;
				 for (int i = 1; i < l; i++)
				 {
					 free(matritsa[i]);
					 free_v3++;
				 }free(matritsa); free_v3++;
				 l--;
				// if (kt > 1) l--;
				 //l = l_p;
				 free(delet_help); free_v3++;
				// for (int a = 0; a < 7; a++) printf("%d ", for_yy2_case[a]);
				 if (for_yy2_case[0] != 0) {
					 free(vendor); 
					 free_v3++;
					 for_yy2_case[0] = 0;
				 }
				 if (for_yy2_case[3]!=0) {
					 free(id); 
					 free_v3++;
					 for_yy2_case[3] = 0;
				 }
				 if (for_yy2_case[1] != 0) {
					 free(model); 
					 free_v3++;
					 for_yy2_case[1] = 0;
				 }
		  }break; //case 3
		  
		  case 4: //update
		  {
			  kt_v4++;
			  tnode* m = list; int lll = 1;
			  while (m != NULL ) {
				  lll++;
				  m = m->ptr;
			  }
			 // printf("%d", lll);
			  l = lll;
			
			  matritsa = (int**)malloc((l) * sizeof(int*)); malloc_v4++;
			  for (int i = 1; i < (l); i++) {
				  matritsa[i] = (int*)malloc(7 * sizeof(int));
				  malloc_v4++;
				  for (int j = 0; j < 7; j++) {
					  matritsa[i][j] = -1;
					 
				  }
			  }
			  l--;
			  int mas_proverka[7] = { 0 }; char name_of_func[22] = { 0 };
			
			  int car_year_new = 0, carrying_new = 0, axles_new = 0; int mas_for_dev_new[6] = { 0 };
			  char* car_vendor_new = 0, * car_model_new = 0, * car_id_new = 0; int chto[7] = { 0 };
			 
			  int car_year = 0, carrying = 0, axles = 0; int mas_for_dev[6] = { 0 };
			  char* car_vendor = 0, * car_model = 0, * car_id = 0, * new_dev =0;
			 
			  char yy2[80] = { 0 }; int for_yy2[7] = { 0 }; char dev[12] = { 0 };
			  int axles_case = 0, carrying_case = 0, car_year_case = 0, cover = 0; int for_search[7] = { 0 };
			  
			  char prev = 0, next = 0;
			  prev = fgetc(in);
			  while (1) {
				  for (int i = 0; i < 22; i++) name_of_func[i] = 0;
				  int i = 0;
				 
				  while (1) {
					 
					  prev = fgetc(in);
					  if (prev == '\n'|| prev == ' ') break;
					 
					  if (prev != ' '&& prev != ',') {
						  
						  name_of_func[i] = prev;
						  if (i == 22) break; i++;
						  if (prev == '=' || prev == '<' || prev == ">") break;
					  }
				  }
				
				 // printf("%s\n", name_of_func);
				  if (prev == ' ' || prev == '\n' ) break;
				  int flag = insert_proverka(name_of_func);
				  if (flag == -1) {
					  flag = proverka_yes(name_of_func);
				  }
				  switch (flag) {
				  case 1: //марка
				  {
					  if (mas_proverka[0] == 0) {
						  if (prev == '=') {
							  chto[0] = 1;
							  char name_car_vendor[15] = { 0 }; i = 0;
							  while (1) {
								  prev = fgetc(in);
								  if (prev == ' ' || prev == '\n' || prev == ',') break;
								  name_car_vendor[i] = prev;  i++;
							  }
							  int k = strlen(name_car_vendor); //printf("%d\n", k);
							  car_vendor_new = (char*)calloc(k + 1, sizeof(char)); calloc_v4++;
							  for (int i = 0; (i < k + 1); i++) {
								  if (name_car_vendor[i] == ',' || name_car_vendor[i] == ' ') break;
								  car_vendor_new[i] = name_car_vendor[i];
							  }
							  

						  }
						  mas_proverka[0] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 2:  //модель
				  {
					  if (mas_proverka[1] == 0) {
						 
						  if (prev == '=') {
							  chto[1] = 1;
							  char name_model[15] = { 0 }; i = 0;
							  while (1) {
								  prev = fgetc(in);
								  if (prev == ' ' || prev == '\n' || prev == ',') break;
								  name_model[i] = prev;  i++;
							  }
							  int k = strlen(name_model); //printf("%d\n", k);
							  car_model_new = (char*)calloc(k + 1, sizeof(char)); calloc_v4++;
							  for (int i = 0; (i < k + 1); i++) {
								  if (name_model[i] == ',' || name_model[i] == ' ') break;
								  car_model_new[i] = name_model[i];
								  //printf("%c", car_vendor[i]);
							  }
							  

						  }
						 

						  mas_proverka[1] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }


				  }break;
				  case 3: //год
				  {
					  if (mas_proverka[2] == 0) {
						
						 
						  if (prev == '=' || prev == '<' || prev == '>') {
							  chto[2] = 1;
							  fscanf(in, "%d", &car_year_new);

						  }
						  

						  mas_proverka[2] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }

				  }break;
				  case 4: //нмоерной знак
				  {


					  if (mas_proverka[3] == 0) {
						 
						  if (prev == '=') {
							  chto[3] = 1;
							  char name_id[15] = { 0 }; i = 0;
							  while (1) {
								  prev = fgetc(in);
								  if (prev == ' ' || prev == '\n' || prev == ',') break;
								  name_id[i] = prev;  i++;
							  }
							  int k = strlen(name_id); //printf("%d\n", k);
							  car_id_new = (char*)calloc(k + 1, sizeof(char)); calloc_v4++;
							  for (int i = 0; (i < k + 1); i++) {
								  if (name_id[i] == ',' || name_id[i] == ' ') break;
								  car_id_new[i] = name_id[i];
								  //printf("%c", car_vendor[i]);
							  }
							 

						  }
						  

						  mas_proverka[3] = 1;
					  }



					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 5: //дивайсы
				  {
					  if (mas_proverka[4] == 0) {
						  chto[4] = 1;
						  int  k = -1; int j = 0, jj = 0; char devise_st[40] = { 0 }; char dev[12] = { 0 };
						  int coma = 0; char q = 0;
						  if (prev == '=') {
							  for_yy2[4] = 5;
							  int r = 0;
							  while (1) {
								  next = fgetc(in);
								  devise_st[r] = next; r++;
								  if (next == '.') {
									  k = proverka(dev);
									  if (k == -1) { printf("not true"); break; }
									  mas_for_dev_new[k] = 1; j = 0;
									  for (int s = 0; s < 12; s++) dev[s] = 0;
								  }
								  if (next == ',') {
									  k = proverka(dev);
									  if (k == -1) { printf("not true"); break; }
									  mas_for_dev_new[k] = 1;
									  i = jj;
									  devise_st[r-1] = '\0';
									  break;
								  }
								  if (next != ',' && next != '.') {
									  dev[j] = next;
									  j++;
									 
								  }
							  }
							  int lenlen = strlen( devise_st);
							  new_dev = (char*)calloc(lenlen, sizeof(char)); calloc_v4++;
							  for (int r = 0; r <= lenlen; r++) {
								  new_dev[r] = devise_st[r];
								  if (new_dev[r] == '.') new_dev[r] = ',';
							  }
						  }

					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 6: //carrying
				  {

					  if (mas_proverka[5] == 0) {
						  if (prev == '=' ) {
							  chto[5] = 1;
							  fscanf(in, "%d", &carrying_new);

						  }
						  
						  mas_proverka[6] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }

				  }break;
				  case 7: //ax
				  {
					  if (mas_proverka[6] == 0) {
						 
						  if (prev == '=' || prev == '<'|| prev == '>') {
							  chto[6] = 1;
							  fscanf(in, "%d", &axles_new);

						  }
						 

						  mas_proverka[6] = 1;
					  }

					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case -1:
				  {
					   printf("%s", name_of_func[i]);
					  printf("not correct");
					  return -2;
				  }break;
				  }
			  }
			 // printf("%d\n", prev);
			  prev = fgetc(in);
			 
			  if (prev == ' ') //ВВОД ДОПОВ
			  {
				  //printf("%d\n", axles);
				  int we = 0;
				  int w = 1;
			  
				  cover = 1;
				  while (w != -1) {
					  switch (w)
					  {
			  
					  case 1:
					  {
						  we = 0; for (int i = 0; i < 80; i++) yy2[i] = 0;
						  while (1) {
							  next = prev;
							  prev = fgetc(in);
			  
							  if (prev == '<' || prev == '>' || prev == '/' || prev == '='  || prev == '\n') break;
							  if (prev != ' ') {
								  yy2[we] = prev;
								  
								  we++;
			  
							  }
						  }
					  }break;
					  }
			  
					  if (prev == ' ' || prev == '\n') break;
					  int k = insert_proverka(yy2);
					  if (k == -1) {
						  k = proverka_yes(yy2);
					  }
					 // printf("%d ", k);
					  if (k == -1) {
						  int q = 0;
						  for (int i = 0; i < 80; i++) {
							  q += yy2[i];
							  if (q != 0)
								  printf("yy2: not true"); break;
						  }
					  }//printf("K_%d\n ", k);
					  for (int o = 0; o < 80; o++) yy2[o] = 0; we = 0;
					  if (prev == '<') {
						  chto[k - 1] = 2;
						  for_yy2[k - 1] = 1;
						  if (k == 7) fscanf(in, "%d", &axles);
						  if (k == 6) fscanf(in, "%d", &carrying);
						  if (k == 3) fscanf(in, "%d", &car_year);
						  // printf("%d ", for_yy2[k - 1]);
					  }
					  if (prev == '>') {
						  chto[k - 1] = 2;
						  for_yy2[k - 1] = 2;
						  if (k == 7) fscanf(in, "%d", &axles);
						  if (k == 6) fscanf(in, "%d", &carrying);
						  if (k == 3) fscanf(in, "%d", &car_year);
			  
						  // printf("%d ", for_yy2[k - 1]);
					  }
					  if (prev == '/') {
						  chto[k - 1] = 2;
						  int wwe = 0;
						  while (wwe < 7) {
							  next = fgetc(in);
							  if (next == '/' || next == '=' || next == '!') break;
							  dev[wwe] = next;
							  wwe++;
						  }
						  int kk = proverka_yes(dev); //printf("\nstat %d\n", kk);
						  for (int o = 0; o < wwe; o++) dev[o] = 0;
						  if (kk == 10) //items
						  {
							  if (next == '/') {
								  wwe = 0;
								  while (wwe < 7) {
									  next = fgetc(in);
									  if (next == '/' || next == '=' || next == '\'') break;
									  dev[wwe] = next;
									  //printf("--%c\n", next);
									  wwe++;
			  
								  }
								  kk = proverka_yes(dev);  
			  
								  for (int o = 0; o < wwe; o++) dev[o] = 0;
								  if (kk == 8) { //include
									  for_yy2[k - 1] = 3;
									  wwe = 0;
									  while (1) {
										  next = fgetc(in);
										  if (next == ',') {
											  kk = proverka(dev); // printf(" \n 2-%d ", kk);
											  if (kk == -1) { printf("not true"); break; }
											  mas_for_dev[kk] = 1; wwe = 0;
											  for (int o = 0; o < 12; o++) dev[o] = 0;
			  
										  }
										  if (next == ']') {
											  kk = proverka(dev);  //printf(" \n 2-%d ", kk);
											  if (kk == -1) { printf("not true"); break; }
											  mas_for_dev[kk] = 1;
											  break;
										  }
										  if (next != '\'' && next != '[' && next != ',' && next != '/') {
											  dev[wwe] = next;
											  wwe++;
										  }
									  }
								  }
								  if (kk == 9) { // in 
									  for_yy2[k - 1] = 7;
									  wwe = 0;
									  while (1) {
										  next = fgetc(in);
										  if (next == ',') {
											  kk = proverka(dev);
											  if (kk == -1) { printf("kk not true\n"); break; }//printf(" \n 2-%d ", kk);
											  mas_for_dev[kk] = 1; wwe = 0;
											  for (int o = 0; o < 12; o++) dev[o] = 0;

										  }
										  if (next == ']') {
											  kk = proverka(dev);
											  if (kk == -1) { printf("kk not true"); break; }//printf(" \n 2-%d ", kk);
											  mas_for_dev[kk] = 1;
											  break;
										  }
										  if (next != '\'' && next != '[' && next != ',') {
											  dev[wwe] = next;
											  // printf("in  %c\n", dev[wwe]); 
											  wwe++;
										  }
									  }
									  //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
								  }
								  if (kk == -1) { printf("not correct"); return -1;; }
							  }
							  else {
								  // prev = fgetc(in); printf("prev %c", prev);
								  if (next == '=') {
									  prev = fgetc(in); //printf("next %c\n", prev);
									  if (prev == '=') {
										  for_yy2[k - 1] = 5;
										  int kk = 0, wwe = 0;
										  while (1)
										  {
											  next = fgetc(in);
											  if (next == ',') {
												  kk = proverka(dev); // printf(" \n 2-%d ", kk);
												  if (kk == -1) { printf("not true"); break; }
												  mas_for_dev[kk] = 1; wwe = 0;
												  for (int o = 0; o < 12; o++) dev[o] = 0;

											  }
											  if (next == ']') {
												  kk = proverka(dev);  //printf(" \n 2-%d ", kk);
												  if (kk == -1) { printf("not true"); break; }
												  mas_for_dev[kk] = 1;
												  break;
											  }
											  if (next != '\'' && next != '[' && next != ',' && next != '/') {
												  dev[wwe] = next;
												  //printf("C %c\n", dev[wwe]);
												  wwe++;
											  }
										  }

									  }
									  else { printf("items==: not true"); return -1; }
									  //printf("%d ", for_yy2[k - 1]);
								  }
								  if (next == '!') {
									  prev = fgetc(in);
									  if (prev == '=')
									  {
										  for_yy2[k - 1] = 6;
										  int kk = 0, wwe = 0;
										  while (1) {
											  next = fgetc(in);
											  if (next == ',') {
												  kk = proverka(dev); // printf(" \n 2-%d ", kk);
												  if (kk == -1) { printf("not true"); break; }
												  mas_for_dev[kk] = 1; wwe = 0;
												  for (int o = 0; o < 12; o++) dev[o] = 0;

											  }
											  if (next == ']') {
												  kk = proverka(dev);  //printf(" \n 2-%d ", kk);
												  if (kk == -1) { printf("not true"); break; }
												  mas_for_dev[kk] = 1;
												  break;
											  }
											  if (next != '\'' && next != '[' && next != ',' && next != '/') {
												  dev[wwe] = next;
												  // printf("C %c\n", dev[wwe]);
												  wwe++;
											  }

										  }
										  // for (int o = 0; o < 6; o++) printf("%d\n", mas_for_dev[o]);
									  }
									  else { printf("not true!="); return -1; }
								  }
							  }
						  }
						  if (kk == 11) //status
						  {
							  wwe = 0;
							  while (wwe < 7) {
								  next = fgetc(in);
								  if (next == '/') break;
								  dev[wwe] = next;
								  //printf("%c\n", dev[wwe]);
								  wwe++;
							  }
							  kk = proverka_yes(dev); //printf("\nstat %d\n", kk);
							  for (int o = 0; o < wwe; o++) dev[o] = 0;
							  if (kk == 9) { // in 
								  for_yy2[k - 1] = 4;
								  wwe = 0;
								  while (1) {
									  next = fgetc(in);
									  if (next == ',') {
										  kk = proverka(dev);
										  if (kk == -1) { printf("kk not true\n"); break; }//printf(" \n 2-%d ", kk);
										  mas_for_dev[kk] = 1; wwe = 0;
										  for (int o = 0; o < 12; o++) dev[o] = 0;

									  }
									  if (next == ']') {
										  kk = proverka(dev);
										  if (kk == -1) { printf("kk not true"); break; }//printf(" \n 2-%d ", kk);
										  mas_for_dev[kk] = 1;
										  break;
									  }
									  if (next != '\'' && next != '[' && next != ',') {
										  dev[wwe] = next;
										  // printf("in  %c\n", dev[wwe]); 
										  wwe++;
									  }
								  }
								  //for (int o = 0; o < 6; o++) printf("%d ", mas_for_dev[o]);
							  }


						  }
					  }
					  if (prev == '=') {
						  prev = fgetc(in);
						  if (prev == '=') {
							  calloc_v4++;
							  chto[k - 1] = 2;
							  char name_of_word[20] = { 0 };
							  if (k == 1) {
								  
								  for_yy2[k - 1] = 8;
								  fscanf(in, "%s", name_of_word);
								  int len = strlen(name_of_word) + 1;
								  car_vendor = (char*)calloc(len, sizeof(char));
								  for (int i = 0; i < len; i++) car_vendor[i] = name_of_word[i];
								  // printf("\n%s\n", vendor);
							  }
							  if (k == 2) {
								  for_yy2[k - 1] = 8;
								  fscanf(in, "%s", name_of_word);
								  int len = strlen(name_of_word) + 1;
								  car_model = (char*)calloc(len, sizeof(char));
								  for (int i = 0; i < len; i++) car_model[i] = name_of_word[i];
							  }
							  if (k == 3) {
								  for_yy2[k - 1] = 8;
								  fscanf(in, "%s", name_of_word);
								  int len = strlen(name_of_word) + 1;
								  car_id = (char*)calloc(len, sizeof(char));
								  for (int i = 0; i < len; i++) car_id[i] = name_of_word[i];
							  }

						  }
 					  }
					  if (prev == '\n') w = -1;
					  if (prev == ' ') w = 1;
				  }
			  }
			 
			  for (int i = 0; i < 7; i++) {
				  if (chto[i] == 1) {
					  for (int j = 1; j <= l; j++) {
						  matritsa[j][i] = 0;
					  }
				  }
			  }
			  int f = 0;
			  for (int t = 0; t < 7; t++) {
				 // printf("%d", chto[t]);
			  }

			  
			  search(list, axles, carrying, car_year, for_yy2, mas_for_dev, 0, devise, counter, car_vendor, car_model, car_id,0);
			 
			  for (int i = 1; i <= l; i++) {
				  for (int j = 0; j < 7; j++) {
					  if (chto[j] == 2) {
						  if (matritsa[i][j] != 0) {
							 matritsa[i][j] = 3;
						  }
						  if (matritsa[i][j] == 0) {
							  matritsa[i][j] = 1;
						  }
					  }
					  //printf("%d\t", matritsa[i][j]);
				  }
				//  printf("\n");
			  }
			  for (int i = 1; i <= l; i++) {
				  for (int j = 0; j < 7; j++) {
					  if (matritsa[i][j] == 3) {
						  for (int m = 0; m < 7; m++) {
							  matritsa[i][m] = 1;
						  }
					  }
				  }
			  }
			 /* for (int i = 1; i <= l; i++) {
				  for (int j = 0; j < 7; j++) {
					  
					  printf("%d\t", matritsa[i][j]);
				  }
				  printf("\n");
			  }*/
			  int x2[7] = { 1, 2,3,4,5,6,7 }; int ii = 0, flag = 7, b = 1;
			  tnode* p = list;
			  while (p != NULL)
			  {
				  if (ii == flag) {
					  ii = 0;
					  p = p->ptr; 
					 if (p == NULL) break;
					  b++;
					  if (b > l)break;
				  }
				  int z = x2[ii];
				  switch (z)
				  {

				  case 1:
				  {
					  if (matritsa[b][0] == 0) {
						  p->car_vendor = car_vendor_new;
						
					  }
				  } break;
				  case 2:
				  {
					  if (matritsa[b][1] == 0) {
						  p->car_model = car_model_new;
						
					  }
				  }break;
				  case 3:
				  {
					  if (matritsa[b][2] == 0) {

						  p->car_year = car_year_new;
						 

					  }

				  }break;
				  case 4:
				  {
					  if (matritsa[b][4] == 0) {
						  p->key = new_dev;
						 
					  }
				  }break;
				  case 5:
				  {
					  if (matritsa[b][3] == 0) {
						  p->car_id = car_id_new;
						 
					  }
				  }break;
				  case 6: {
					  if (matritsa[b][5] == 0) {
						  p->carrying = carrying_new;
						 
					  }
				  }break;
				  case 7:
				  {
					  if (matritsa[b][6] == 0) {
						  p->axles = axles_new;
						  
					  }
				  }break;
				  }

				  ii++;
			  }
			  int zapisi = 0;
			  for (int i = 1; i < l; i++) {
				  for (int j = 0; j < 7; j++) {
					  if (matritsa[i][j] == 0) {
						  for (int z = 0; z < 7; z++) matritsa[i][z] = 0;
					  }
				  }
				  if (matritsa[i][0] != 1)
				  {
					  if (matritsa[i][1] != 1) {
						  if (matritsa[i][2] != 1) {
							  if (matritsa[i][3] != 1) {
								  if (matritsa[i][4] != 1) {
									  if (matritsa[i][5] != 1) {
										  if (matritsa[i][6] != 1) zapisi++;
									  }
								  }

							  }
						  }
					  }
				  }
			  }
			  printf("\nupdate:%d\n", zapisi);
			 
			  l++;
			  for (int i = 1; i < l; i++) {
				  free(matritsa[i]);
				  free_v4++;
			  }
			  free(matritsa); free_v4++;
			   l --;
			   if (mas_proverka[0] != 0) {
				  // free(car_vendor_new); free_v4++;
				   free(car_vendor); free_v4++;
			   }
			   if (mas_proverka[1] != 0) {
				   free_v4++;
				   free(car_model); //free_v4++;
			   }
			   if (mas_proverka[3] != 0) {
				   //free(car_id_new); free_v4++;
				   free(car_id); free_v4++;
			   }
			   if (mas_proverka[4] != 0) {
				  // free(new_dev); free_v4++;
				  // free(car_vendor); free_v4++;
			   }

          }break; // case4

		  case 5: //unic
		  {
			  int save_l = 0, l_prev = 0;;
			  int de = 0;
			  tnode* m = list; int lll = 1;
			  while (m != NULL) {
				  lll++;
				  m = m->ptr;
			  }
			   //printf("aa%d", lll);
			  l = lll;
			  
			  save_l = l;
			  matritsa = (int**)malloc((l) * sizeof(int*)); malloc_v5++;
			  for (int i = 1; i < (l); i++) {
				  matritsa[i] = (int*)malloc(7 * sizeof(int)); malloc_v5++;
				  for (int j = 0; j < 7; j++) {
					  matritsa[i][j] = -1;

				  }
			  }
			  
			  int sh[7] = { 0 };

			  int mas_proverka[7] = { 0 }; char name_of_func[22] = { 0 }; int for_yy2[7] = { 0 }; int mas_for_dev[6] = { 0 };

			  int car_year = 0, carrying = 0, axles = 0, deletee =0; 
			  char* car_vendor = 0, * car_model = 0, * car_id = 0, *key=0; int chto[7] = { -1 };

			  for (int i = 0; i < 7; i++) chto[i] = -1;
			  char prev = 0, next = 0;
			  prev = fgetc(in);
			  int chto_v2[7] = { 0 };
			  
			  while (1) {
				  for (int i = 0; i < 22; i++) name_of_func[i] = 0;
				  int i = 0;
				  while (1) {
					  prev = fgetc(in);
					  if (prev == '\n' || prev == ' ') break;
					  if (prev != ' ') {
						  if (prev == '\n' || prev == ',') break;
						  name_of_func[i] = prev;
						  if (i == 22) break; i++;
						  if (prev == '=' || prev == '<' || prev == ">") break;
					  }
				  }

					 int flag = proverka_yes(name_of_func);
					 chto[flag - 1] = 1;
				  switch (flag) {
				  case 1: //марка
				  {
					  if (mas_proverka[0] == 0) {
							
						  mas_proverka[0] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 2:  //модель
				  {
					  if (mas_proverka[1] == 0) {
							 
							 mas_proverka[1] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }


				  }break;
				  case 3: //год
				  {
					  if (mas_proverka[2] == 0) {
                         
						  mas_proverka[2] = 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }

				  }break;
				  case 4: //нмоерной знак
				  {
					  if (mas_proverka[3] == 0) {
							
							  mas_proverka[3] == 0;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 5: //дивайсы
				  {
					  if (mas_proverka[4] == 0) {
						  key = (char*)calloc(1, sizeof(char)); calloc_v5++;
						  mas_proverka[4] == 0;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 6: //carrying
				  {
					  if (mas_proverka[5] == 0) {
							 
							  mas_proverka[5] == 1;
					  }
					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case 7: //ax
				  {
					  if (mas_proverka[6] == 0) {
							 
						  mas_proverka[6] = 1;
					  }

					  else {
						  printf("not correct");
						  return 500;
					  }
				  }break;
				  case -1:
				  {
					  //  for (int i = 0; i < 22; i++) printf("%c", name_of_func[i]);
					  printf("not correct");
					  return -2;
				  }break;
				  }
				  if (prev == ' ' || prev == '\n') break;
               }
			 tnode* t = list;
			  int flag = 0, step[7] = { 0 };
			  for (int i = 0; i < 7; i++) {
				  if (chto[i] == 1) flag++;
				  //printf("%d ", chto[i]);
			  }
			  for (int i = 0; i < 7; i++) chto_v2[i] = chto[i];
			  tnode* p = list;
			  int uniq = l;
			  int d = 0, len = 0, lvl = 0, kostyl =0;
			 
			  while (p != NULL) {
				  if (kostyl == 0)  p = list;
				  
				  if (p == NULL) break;
				  d = lin_search(chto);
				  if (d != -1) {
					  chto[d] = -1;
				  
				  }
				  if (d == -1) {
					 
					  
				  }
				  
				  if (lvl == flag) {
					  search(list, axles, carrying, car_year, for_yy2, mas_for_dev, 0, devise, counter, car_vendor, car_model, car_id, 0);
					  //l--;
					 de =    analiz(flag, l, 1);
					

					 if (de == 0) {
						 for (int i = 1; i < l; i++) {
							 if (matritsa[i][0] == 0) de = 1;
						 }
						 if (de == 0) {
							 lvl = 0;
							 for (int i = 0; i < 7; i++)   chto[i] = chto_v2[i];
							 kostyl = 1;
							
							 p = p->ptr;
							 continue;
						 }
						 
						
					 }
					
					 if (de > 0 ) {
						// printf("\n");
						 list = for_delet(list, de, chto);
						 tnode* new = list; int ll = 1;
						 while (new != NULL) {
							// printf(" %s %d %s \n", new->car_vendor, new->car_year, new->car_model);
							 
							 ll++;
							 new = new->ptr;
						 }
						 for (int i = 1; i < l; i++) {
							 for (int j = 0; j < 7; j++) {
								 matritsa[i][j] = -1;
							 }

						 }
						 l = ll;
						 p = list;
						 d = -1;
						 lvl = 0;
						 for (int i = 0; i < 7; i++)   chto[i] = chto_v2[i];
						 
						 if (p == NULL) break;
						 continue;
					 
					 
					 
					 }
				   }
				 
				  switch (d) {
				  case 0:
				  {
					  for_yy2[d] = 8;
					  step[0]++;
					  len = strlen(p->car_vendor);
					  if (step[0] == 1) {
						  car_vendor = (char*)calloc(len, sizeof(char)); calloc_v5++;
					  }
					  if (step[0] > 1) {
						  car_vendor = (char*)realloc(car_vendor, len); realloc_v5++;
					  }
					  strcpy(car_vendor, p->car_vendor);
					  lvl++;
				  }break;
				  
				  case 1:
				  {
					  for_yy2[d] = 8;
					  step[1]++;
					  len = strlen(p->car_model);
					  if (step[1] == 1) {
						  car_model = (char*)calloc(len, sizeof(char)); calloc_v5++;
					  }
					  if (step[1] > 1) {
						  car_model = (char*)realloc(car_model, len); realloc_v5++;
					  }
					  strcpy(car_model, p->car_model);
					  lvl++;
				  }break;

				  case 2:
				  {
					  for_yy2[d] = 8;
					  lvl++;
					  car_year = p->car_year;
				  }break;
				  case 3:
				  {
					  for_yy2[d] = 8;
					  step[3]++;
					  len = strlen(p->car_id);
					  if (step[3] == 1) {
						  car_id = (char*)calloc(len, sizeof(char)); calloc_v5++;
					  }
					  if (step[3] > 1) {
						  car_id = (char*)realloc(car_id, len); realloc_v5++;
					  }
					  strcpy(car_id, p->car_id);
					  lvl++;
				  }break;
				  
				  case 4:
				  {
					  
					  char *key_v = 0;
					  for_yy2[d] = 5;
					  step[4]++;
					  len = strlen(p->key);
					  
					  key = (char*)realloc(key, len); realloc_v5++;
						//  key_v = (char*)calloc(len, sizeof(char));
					  
					  
					  strcpy(key, p->key); //strcpy(key_v, p->key);
					  forenum(key);
					  for (int o = 0; o < 6; o++) {
						  mas_for_dev[o]=  know[o];
						 // printf("%d", mas_for_dev[o]);

					  }
					  lvl++;
					  
					  
				  }break;
				  case 5:
				  {
					  for_yy2[d] = 8;
					  lvl++;
					  carrying = p->carrying;
				  }break;
				  
				  case 6:
				  {
					  for_yy2[d] = 8;
					  lvl++;
					  axles = p->axles;
				  }break;
				  case -1: break;
				  }
				  
			  
			  }
			  um = 0;
			  l_prev = 0;
			  l = save_l;
			  for (int i = 1; i < l; i++) {
				  free(matritsa[i]);
				  free_v5++;
			  }
			  free(matritsa); free_v5++;
			  l = l_prev;
			  uniq -= l;
			  if (chto_v2[0] != -1) {
				   free_v5++;
			 }
			  if (chto_v2[1] != -1) {
				   free_v5++;
			  }
			  if (chto_v2[3] != -1) {
				   free_v5++;
			  }
			  if (chto_v2[4] != -1) {
				  free_v5++;
			  }
			  printf("uniq:%d\n", uniq);
           }break;
		  case 6: { //exit
			  remove_all(list);
			  fprintf(out, "\nlist:\nmalloc=%d;\ncalloc=%d;\nrealloc=%d;\nfree=%d\n", malloc_os, calloc_os, realloc_os, free_os);
			  fprintf(out, "\nvvod:\nmalloc=%d;\ncalloc=%d;\nrealloc=%d;\nfree=%d\n", malloc_v1+ malloc_v2+ malloc_v3+ malloc_v4+ malloc_v5,  calloc_v2 + calloc_v3 + calloc_v4 + calloc_v5, realloc_v1 + realloc_v2 + realloc_v3 + realloc_v4 + realloc_v5,  free_v2 + free_v3 + free_v4 + free_v5);
			  fclose(in); fclose(out);
			  return 0;
		   } break;

		   case -1: { //exit
			   printf("%s\n", y);
			   printf("\nnot correct");
				return -90;
			} break;
		}

	}
	
}
