const int MAXN = 200;
int c1[MAXN+10] , c2[MAXN+10];
void part() {
    int i , j , k;
    for (int i = 0 ; i <= MAXN ; i ++) {
        c1[i] = 1 , c2[i] = 0;
    }
    for (int k = 2 ; k <= MAXN ; k ++) {
        for (int i = 0 ; i <= MAXN ; i ++) {
            for (int j = 0 ; j + i <= MAXN ; j += k) {
                c2[i+j] += c1[i];
            }
            for (int i = 0 ; i <= MAXN ; i ++) {
                c1[i] = c2[i] ; c2[i] = 0;
            }
        }
    }
}
