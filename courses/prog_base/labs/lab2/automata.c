int run(int moves[], int movesLen, int res[], int resLen){
    enum command {REPEAT, POP, BREAK, CONTINUE, PUSH, ERROR};
    struct jump {
        enum command x;
        int state;
    } tabl[4][4];
    int elements[4] = {8,12,17,107};
    int push[4][4];
    tabl[0][0].x=PUSH; tabl[0][0].state=1; push[0][0]=12;
    tabl[0][1].x=CONTINUE; tabl[0][1].state=1;
    tabl[0][2].x=PUSH; tabl[0][2].state=2; push[0][2]=13;
    tabl[0][3].x=BREAK; tabl[0][3].state=0;
    tabl[1][0].x=ERROR; tabl[1][0].state=0;
    tabl[1][1].x=CONTINUE; tabl[1][1].state=2;
    tabl[1][2].x=PUSH; tabl[1][2].state=3; push[1][2]=14;
    tabl[1][3].x=POP; tabl[1][3].state=2;
    tabl[2][0].x=POP; tabl[2][0].state=3;
    tabl[2][1].x=CONTINUE; tabl[2][1].state=3;
    tabl[2][2].x=POP; tabl[2][2].state=0;
    tabl[2][3].x=PUSH; tabl[2][3].state=1; push[2][3]=15;
    tabl[3][0].x=PUSH; tabl[3][0].state=0; push[3][0]=18;
    tabl[3][1].x=CONTINUE; tabl[3][1].state=0;
    tabl[3][2].x=PUSH; tabl[3][2].state=2; push[3][2]=16;
    tabl[3][3].x=REPEAT; tabl[3][3].state=1;
    int i=0, st=0, len=0;
    while (i<movesLen)
    {
        int k = -1;
        if (moves[i]==elements[0]){
                k = 0;
        }
        else if (moves[i]==elements[1]){
                k = 1;
        }
        else if (moves[i]==elements[2]){
                k = 2;
        }
        else if (moves[i]==elements[3]){
                k = 3;
        }
        if (k==-1){
                break;
        }
        struct jump q=tabl[st][k];
        int w=push[st][k];
        if (q.x==POP) {
            if (len==0){
                break;
            }
            else{
                len--;
            }
            i++;
        }
        else if (q.x==BREAK||q.x==ERROR){
                break;
        }
        else if (q.x==CONTINUE){
                i++;
        }
        else if (q.x==PUSH) {
            res[len] = w;
            len++;
            if (len==resLen){
                break;
            }
            i++;
        }
        st=q.state;
    }
int j;
for(j=len; j<resLen; j++){
    res[j] = 0;
    }
return len;
}
