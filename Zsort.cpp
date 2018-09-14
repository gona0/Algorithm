int partition(int p, int r){
    int j = p - 1;
    Hole temp;
    for (int i = p; i < r; i++){
        if (hole[i].cost < hole[r].cost){
            j++;
            temp = hole[i];
            hole[i] = hole[j];
            hole[j] = temp;
        }
    }
    j++;
    temp = hole[r];
    hole[r] = hole[j];
    hole[j] = temp;
    return j;
}
 
void Qsort(int p, int r){
    if (p < r){
        int q = partition(p, r);
        Qsort(p, q - 1);
        Qsort(q + 1, r);
    }
}
