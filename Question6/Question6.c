    #include <assert.h>
    #include <limits.h>
    #include <math.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char* readline();
    char** split_string(char*);
    typedef struct{
        char name;
        int department;
        int group;
    }Employee; 
    typedef struct{
        char* member;
        int max[3];
        int total;
    }Group;
    // typedef struct {
    //     char request[2];
    // }Request;
    void sortPrint(Group group){
        int i, j;char temp;
        for (i = 0; i < group.total-1; i++) {
            for (j = i+1; j < group.total; j++) {
                if (group.member[i] > group.member[j]) {
                temp = group.member[i];
                group.member[i] = group.member[j];
                group.member[j] = temp;
                }
            }
        }
        for(i=0;i<group.total;i++){
            printf("%c\n",group.member[i]);
        }
    }
    void merge(Group* group1,Group* group2){
        int i;
        for (i=0;i<3;i++){
            group1->max[i]+=group2->max[i];
            group2->max[i]=0;
        }
        group1->total+=group2->total;
        group2->total=0;

        strcat(group1->member,group2->member);
        strcpy(group2->member,"");
    }
    Employee* findEmployee(Employee* employees,char first, int n){
        int i;
        for(i=0;i<n;i++){
            if(employees[i].name==first){
                return &employees[i];
            }
        }
    }
    // Complete the theHackathon function below.
    void theHackathon(int n, int m, int a, int b, int f, int s, int t) {
        int i,j;
        Employee employees[n];
        Group groups[n];
        char requests[m][2];
        //initialize employees
        for (i=0;i<n;i++){
            // need space before %c to ignore 'enter' 
            scanf(" %c",&(employees[i].name));
            scanf("%d",&(employees[i].department));
            employees[i].group=i;
        }
        //initialize requests
        for (i=0;i<m;i++){
            scanf(" %c",&(requests[i][0]));
            scanf(" %c",&(requests[i][1]));
        }
        //initialize groups
        for (i=0;i<n;i++){
            groups[i].total=1;
            groups[i].member=malloc(n*sizeof(char));
            groups[i].member[0]=employees[i].name;
            groups[i].member[1]='\0';
            for(j=0;j<3;j++){
                groups[i].max[j]=0;
            }
            groups[i].max[employees[i].department-1]=1;
        }
        // main code
        int groupof1,groupof2;
        char first,second;
        Employee *firstEmp,*secondEmp,*employee;
        for (i=0;i<m;i++){
            first = requests[i][0];
            second = requests[i][1];
            firstEmp = findEmployee(employees,first,n);
            secondEmp = findEmployee(employees,second,n);
            groupof1 = firstEmp->group;
            groupof2 = secondEmp->group;
            // if 2 employees not in the same group
            if ((groupof1!=groupof2) 
            && (groups[groupof1].total+groups[groupof2].total <= b) 
            && (groups[groupof1].max[0]+groups[groupof2].max[0]<=f) 
            && (groups[groupof1].max[1]+groups[groupof2].max[1]<=s) 
            && (groups[groupof1].max[2]+groups[groupof2].max[2]<=t)){
                for(j=0;j<strlen(groups[groupof2].member);j++){
                    employee=findEmployee(employees,groups[groupof2].member[j],n);
                    employee->group=groupof1;
                }
                merge(&groups[groupof1],&groups[groupof2]);
            }
        }
        
        // check every group to find largest number of elements
        int max=0;
        for(i=0;i<n;i++){
            if ( groups[i].total>max){
                max=groups[i].total;
            }
        }
        if(max<a){
            printf("no groups");
            return;
        }
        //print
        Group result;
        for(j=0;j<3;j++){
            result.max[j]=0;
        }
        result.total=0;
        strcpy(result.member,"");
        for(i=0;i<n;i++){
            if(groups[i].total == max){
                merge(&result,&groups[i]);
            }
        }
        sortPrint(result);
    }

    int main()
    {
        char** inputvalue = split_string(readline());

        char* n_endptr;
        char* n_str = inputvalue[0];
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* m_endptr;
        char* m_str = inputvalue[1];
        int m = strtol(m_str, &m_endptr, 10);

        if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

        char* a_endptr;
        char* a_str = inputvalue[2];
        int a = strtol(a_str, &a_endptr, 10);

        if (a_endptr == a_str || *a_endptr != '\0') { exit(EXIT_FAILURE); }

        char* b_endptr;
        char* b_str = inputvalue[3];
        int b = strtol(b_str, &b_endptr, 10);

        if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

        char* f_endptr;
        char* f_str = inputvalue[4];
        int f = strtol(f_str, &f_endptr, 10);

        if (f_endptr == f_str || *f_endptr != '\0') { exit(EXIT_FAILURE); }

        char* s_endptr;
        char* s_str = inputvalue[5];
        int s = strtol(s_str, &s_endptr, 10);

        if (s_endptr == s_str || *s_endptr != '\0') { exit(EXIT_FAILURE); }

        char* t_endptr;
        char* t_str = inputvalue[6];
        int t = strtol(t_str, &t_endptr, 10);

        if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

        theHackathon(n, m, a, b, f, s, t);

        return 0;
    }

    char* readline() {
        size_t alloc_length = 1024;
        size_t data_length = 0;
        char* data = malloc(alloc_length);

        while (true) {
            char* cursor = data + data_length;
            char* line = fgets(cursor, alloc_length - data_length, stdin);

            if (!line) { break; }

            data_length += strlen(cursor);

            if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

            size_t new_length = alloc_length << 1;
            data = realloc(data, new_length);

            if (!data) { break; }

            alloc_length = new_length;
        }

        if (data[data_length - 1] == '\n') {
            data[data_length - 1] = '\0';
        }

        data = realloc(data, data_length);

        return data;
    }

    char** split_string(char* str) {
        char** splits = NULL;
        char* token = strtok(str, " ");

        int spaces = 0;

        while (token) {
            splits = realloc(splits, sizeof(char*) * ++spaces);
            if (!splits) {
                return splits;
            }

            splits[spaces - 1] = token;

            token = strtok(NULL, " ");
        }

        return splits;
    }

