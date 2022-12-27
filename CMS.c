#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define mahjong options
#define START_POINT 25000
#define TH_POINT 30000

// select UMA
// mode 515: 5-15
// mode 1020: 10-20
// mode 1030: 10-30
#ifndef MODE_UMA
#define MODE_UMA 515
#endif

// define text file option
#define MJ_TXT_INPUT "./input/mj_input.txt"
#define MJ_TXT_OUTPUT "./output/mj_output.txt"
#define MJ_TXT_OUTPUT_TIME "./output/mj_output_%y%m%d_%H%M_%S.txt"

#define MAXBUF 100

typedef struct mj_player {
    char *name[MAXBUF];
    int mj_point;
    int rank;
    float mj_score;
} MJ_PLAYER;

void print_result(FILE *fp, MJ_PLAYER *player);

int main() {
    FILE *fp, *fp_out;
    MJ_PLAYER player[4];
    float tmp_score = 0.0;
    int uma_low = 0, uma_high = 0;
    char string_buf[MAXBUF];
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    int i, j;

    if ((fp = fopen(MJ_TXT_INPUT, "r")) == NULL) {
        fprintf(stderr, "Can't open text file.\n");
        exit(1);
    }

    strftime(string_buf, sizeof(string_buf), MJ_TXT_OUTPUT_TIME, tm_now);
    fp_out = fopen(string_buf, "w");
    for (i = 0; i < 4; i++) {
        fscanf(fp, "%s%d", player[i].name, &player[i].mj_point);
    }

    switch (MODE_UMA) {
        case 1:
        case 515:
            uma_low = 5;
            uma_high = 15;
            break;
        case 2:
        case 1020:
            uma_low = 10;
            uma_high = 20;
            break;
        case 3:
        case 'M':
        case 1030:
            uma_low = 10;
            uma_high = 30;
            break;
        case 4:
        case 2030:
            uma_low = 20;
            uma_high = 30;
            break;
        default:
            uma_low = 5;
            uma_high = 15;
            break;
    }

    strftime(string_buf, sizeof(string_buf), "%Y/%m/%d %H:%M:%S %A", tm_now);
    // printf("%s", asctime(localtime(&now)));
    printf("Time: %s\n", string_buf);
    printf("Uma: %d-%d\n\n", uma_low, uma_high);
    fprintf(fp_out, "Time: %s\n", string_buf);
    fprintf(fp_out, "Uma: %d-%d\n\n", uma_low, uma_high);

    // sort reverse player[i].mj_point with bubble sort
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (player[j].mj_point < player[j + 1].mj_point) {
                MJ_PLAYER tmp = player[j];
                player[j] = player[j + 1];
                player[j + 1] = tmp;
            }
        }
    }

#ifdef DEBUG
    for (i = 0; i < 4; i++) {
        fprintf(stderr, "%s %d\n", player[i].name, player[i].mj_point);
    }
#endif

    // calc rank
    for (i = 0; i < 4; i++) {
        player[i].rank = i + 1;
    }

    // calc mj_score
    for (i = 0; i < 4; i++) {
        tmp_score = (float)player[i].mj_point - (float)TH_POINT;
        tmp_score /= 1000.0;

#ifdef DEBUG
        fprintf(stderr, "%s %.1f\n", player[i].name, tmp_score);
#endif

        switch (player[i].rank) {
            case 1:
                player[i].mj_score = tmp_score + (float)uma_high;
                player[i].mj_score +=
                    (float)(TH_POINT - START_POINT) * 4 / 1000.0;
                break;
            case 2:
                player[i].mj_score = tmp_score + (float)uma_low;
                break;
            case 3:
                player[i].mj_score = tmp_score - (float)uma_low;
                break;
            case 4:
                player[i].mj_score = tmp_score - (float)uma_high;
                break;
        }
    }

    // print result
    print_result(fp_out, player);

    fclose(fp);
    fclose(fp_out);

    return 0;
}

void print_result(FILE *fp, MJ_PLAYER *player) {
    int i;
    printf("rank:   name    : point : score\n");
    fprintf(fp, "rank:   name    : point : score\n");
    for (i = 0; i < 4; i++) {
        printf("[%d] : %-10s: %5d : %+.1f\n", player[i].rank, player[i].name,
               player[i].mj_point, player[i].mj_score);
        fprintf(fp, "[%d] : %-10s: %5d : %+.1f\n", player[i].rank,
                player[i].name, player[i].mj_point, player[i].mj_score);
    }
}