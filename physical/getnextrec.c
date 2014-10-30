#include "../include/globals.h"
#include "../include/getnextrec.h"
#include "../include/readpage.h"

#define FOUND 1
#define NOT_FOUND 0

/**
 * Gets the next record in sequential scan
 * @param relNum
 * @param startRid
 * @param foundRid
 * @param recPtr
 *
 * @return flag - Found or not found
 */
int GetNextRec(int relNum, Rid *startRid, Rid *foundRid, char *recPtr) {
    int recsPerPg = g_catcache[relNum].recsPerPg;
    int numPgs = g_catcache[relNum].numPgs;
    int flag = NOT_FOUND;

    Rid curRid = getNextRid(startRid->pid, startRid->slotnum, recsPerPg, numPgs);
    Rid prevRid = curRid;

    while (curRid.pid <= numPgs && flag == NOT_FOUND) {
        if (curRid.pid == 0) { //Reached the end of records
            break;
        }
        ReadPage(relNum, curRid.pid);
        while (curRid.slotnum >= prevRid.slotnum) { //Loop till the end of cur page

            /*Check the slotmap to see if it is in use*/
            if (g_buffer[relNum].page.slotmap & (1 << curRid.slotnum)) {
                flag = FOUND;
                int offset = g_catcache[relNum].recLength * (curRid.slotnum - 1);
                recPtr = g_buffer[relNum].page.contents + offset;
                break;
            }

            prevRid = curRid;
            curRid = getNextRid(curRid.pid, curRid.slotnum, recsPerPg, numPgs);
            if (curRid.slotnum == 0) { //Reached the end of records
                break;
            }

        }
    }
    return flag;
}

/**
 *Gets the next Rid in sequence
 *
 * @param   curPid
 * @param   curSlot
 * @param   recsPerPg
 * @param   numPgs
 * @return  the nextRid
 *          {0,0} if no next
 */
Rid getNextRid(short curPid, short curSlot, int recsPerPg, int numPgs) {
    Rid nextRid = { 0, 0 };
    if (curSlot == recsPerPg && curPid == numPgs) {
        return nextRid;
    } else if (curSlot == recsPerPg) {
        nextRid.slotnum = 1;
        nextRid.pid = curPid + 1;
    } else {
        nextRid.pid = curPid;
        nextRid.slotnum = curSlot;
    }
    return nextRid;
}