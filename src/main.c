////////////////////////////////////////
// { ACRCNEDT } { 0.0.1 }
// Author: epsilon5
// License: invalid
// Description: map editor for Ace Recon
////////////////////////////////////////

//[commandz] Like, `char* menutext = NULL;` and then `menutext = "Speedy"`
//4:52:31 PM [#] [commandz] You can use a pointer, and then just assign that pointer to the
//constant string

/* Keep these headers */
#define FORCE_INTERRUPTS
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
/* Other available headers */
// including stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h
/* Available libraries */
// including lib/ce/graphc.h, lib/ce/fileioc.h, and lib/ce/keypadc.h
// Sample: #include <lib/ce/graphc.h>
#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>
#include <intce.h>
#include <tice.h>
#include <math.h>
#define fabsf

/* Put function prototypes here */
char Appvars[9][10];
char currpackname[9];
char search_String[] = "ACE";
short numlevels = 20;

void BlaText(void) {
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(255);
    gfx_SetTextTransparentColor(0);
}
void WhiText(void) {
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);
}

void ErrorMessage(char str1[], char str2[]) {
    short length;
    gfx_SetTextScale(1, 1);
    length = gfx_GetStringWidth(str2);
    gfx_Blit(1);
    gfx_SetColor(0);
    gfx_FillRectangle(155 - length / 2, 98, length + 10, 45);
    gfx_SetColor(74);
    gfx_Rectangle(155 - length / 2, 98, length + 10, 45);
    gfx_Rectangle(156 - length / 2, 99, length + 8, 43);
    gfx_SetTextScale(2, 2);
    length = gfx_GetStringWidth(str1);
    gfx_PrintStringXY(str1, 160 - length / 2, 103);
    gfx_SetTextScale(1, 1);
    length = gfx_GetStringWidth(str2);
    gfx_PrintStringXY(str2, 160 - length / 2, 125);
    gfx_SwapDraw();
    while (!(kb_Data[6] & kb_Enter)) {
        kb_Scan();
    }
    while (kb_Data[6] & kb_Enter) {
        kb_Scan();
    }
}

void saveAs() {
    char str1[] = "Pack creation is in progress.";
    uint8_t MapData[14][10];
    short initialize = 5;
    short width;
    uint8_t length = 0;
    uint8_t i = 0, skKey;
    uint8_t j = 0, k;
    short upper = 0;
    bool write = true;
    short numlevels = 20;
    ti_var_t slota;
    char newPackName[9];
    const char *chars = "\0\0\0\0\0\0\0\0\0\0\0WRMH\0\0\0\0VQLG\0\0\0ZUPKFC\0\0YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0\0";
    const char *chart = "\0\0\0\0\0\0\0\0\0\0\0wrmh\0\0\0\0vqlg\0\0\0zupkfc\0\0ytojeb\0\0xsnida\0\0\0\0\0\0\0\0\0";
    typedef struct {
        uint8_t type;
        uint16_t x;
        uint16_t y;
        float angle;
        float attangle;
    } guard_t;
    guard_t guard[5];
    for(j = 0; j < 10; ++j) {
        for(k = 0; k < 14; ++k) {
            MapData[k][j] = 0;
        }
    }
    for (j = 0; j < 5; ++j) {
        guard_t *g = &guard[j];
        g->x = 0;
        g->y = 0;
        g->angle = 0;
        g->attangle = 0;
        g->type = 1;
    }
    BlaText();
    while (os_GetCSC());
    gfx_SetColor(0);
    gfx_FillRectangle(115, 98, 90, 45);
    gfx_SetColor(74);
    gfx_Rectangle(115, 98, 90, 45);
    gfx_Rectangle(116, 99, 88, 43);
    gfx_SetTextScale(2, 2);
    strcpy(str1, "Name?");
    length = gfx_GetStringWidth(str1);
    gfx_PrintStringXY(str1, 160 - length / 2, 103);
    gfx_SetTextScale(1, 1);
    gfx_SetColor(0);
    while (((skKey = os_GetCSC()) != sk_Enter) || i < 2) {
        gfx_SetColor(0);
        gfx_FillRectangle_NoClip(125, 125, 74, 12);
        if (chars[skKey] && i < 8) {
            if (upper == 0) {
                newPackName[i++] = chars[skKey];
            }
            if (upper == 1) {
                newPackName[i++] = chart[skKey];
            }
            if (upper == 2) {
                if (skKey == sk_0) {
                    newPackName[i++] = "0"[0];
                }
                if (skKey == sk_1) {
                    newPackName[i++] = "1"[0];
                }
                if (skKey == sk_2) {
                    newPackName[i++] = "2"[0];
                }
                if (skKey == sk_3) {
                    newPackName[i++] = "3"[0];
                }
                if (skKey == sk_4) {
                    newPackName[i++] = "4"[0];
                }
                if (skKey == sk_5) {
                    newPackName[i++] = "5"[0];
                }
                if (skKey == sk_6) {
                    newPackName[i++] = "6"[0];
                }
                if (skKey == sk_7) {
                    newPackName[i++] = "7"[0];
                }
                if (skKey == sk_8) {
                    newPackName[i++] = "8"[0];
                }
                if (skKey == sk_9) {
                    newPackName[i++] = "9"[0];
                }
            }
        }
        if (i == 0) {
            upper = 0;
        }
        if ((skKey == sk_Del) && (i > 0)) {
            newPackName[i--] = '\0';
        }
        if (skKey == sk_Clear) {
            write = false;
            while (kb_Data[6] & kb_Clear) {
                kb_Scan();
            }
            break;
        }
        if (skKey == sk_Alpha) {
            upper++;
            if (upper > 2) {
                upper = 0;
            }
        }
        newPackName[i] = '\0';
        length = gfx_GetStringWidth(newPackName);
        if (i < 8) {
            gfx_SetColor(7);
            gfx_SetTextFGColor(7);
            gfx_FillRectangle(127 + length, 133, 9 - (upper == 2), 2);
            if (upper == 0) {
                gfx_PrintStringXY("A", 128 + length, 125);
            }
            if (upper == 1) {
                gfx_PrintStringXY("a", 128 + length, 125);
            }
            if (upper == 2) {
                gfx_PrintStringXY("1", 128 + length, 125);
            }
            gfx_SetTextFGColor(255);
        }
        gfx_PrintStringXY(newPackName, 127, 126);
        gfx_SwapDraw();
        gfx_BlitScreen();
    }
    while (kb_Data[6] & kb_Enter) {
        kb_Scan();
    }
    if (write) {
        while (!(kb_Data[6] & kb_Enter)) {
            kb_Scan();
            gfx_SetColor(0);
            gfx_FillRectangle(100, 98, 120, 45);
            gfx_SetColor(74);
            gfx_Rectangle(100, 98, 120, 45);
            gfx_Rectangle(101, 99, 118, 43);
            gfx_SetTextScale(2, 2);
            strcpy(str1, "Levels?");
            length = gfx_GetStringWidth(str1);
            gfx_PrintStringXY(str1, 160 - length / 2, 103);
            gfx_SetTextScale(1, 1);
            sprintf(str1, "< %d >", numlevels);
            length = gfx_GetStringWidth(str1);
            gfx_PrintStringXY(str1, 160 - length / 2, 125);
            if ((kb_Data[7] & kb_Left) && (numlevels > 1)) {
                numlevels--;
                while (kb_Data[7] & kb_Left) {
                    kb_Scan();
                }
            }
            if ((kb_Data[7] & kb_Right) && (numlevels < 50)) {
                numlevels++;
                while (kb_Data[7] & kb_Right) {
                    kb_Scan();
                }
            }
            gfx_SwapDraw();
        }
        while (kb_Data[6] & kb_Enter) {
            kb_Scan();
        }
        ti_CloseAll();
        if (!(slota = ti_Open(newPackName, "r"))) {
            ti_CloseAll();
            slota = ti_Open(newPackName, "w");
            ti_Write(&search_String, sizeof(search_String), 1, slota);
            ti_Write(&numlevels, 1, 1, slota);
            for (j = 0; j < numlevels; ++j) {
                ti_Write(&MapData, 140, 1, slota);
                gfx_SetTextScale(1, 1);
                strcpy(str1, "Creation in progress.");
                width = gfx_GetStringWidth(str1);
                gfx_SetColor(0);
                gfx_FillRectangle(155 - (width / 2), 90, width + 10, 60);
                gfx_SetColor(74);
                gfx_Rectangle(155 - (width / 2), 90, width + 10, 60);
                gfx_Rectangle(156 - (width / 2), 91, width + 8, 58);
                gfx_SetTextScale(1, 1);
                gfx_PrintStringXY(str1, 160 - (width / 2), 117);
                gfx_SetColor(7);
                gfx_FillRectangle(160 - ((width - 10) / 2), 132, (width - 10) * j / numlevels, 8);
                gfx_SetColor(74);
                gfx_Rectangle(160 - ((width - 8) / 2), 131, width - 8, 10);
                gfx_Rectangle(160 - ((width - 10) / 2), 132, width - 10, 8);
                sprintf(str1, "%d%s", 100 * j / numlevels, "%");
                gfx_SetTextScale(2, 2);
                length = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 160 - length / 2, 95);
                gfx_Blit(1);
                ti_Write(&initialize, 1, 1, slota);
                for (k = 0; k < 5; ++k) {
                    guard_t *g = &guard[k];
                    ti_Write(&g->x, 2, 1, slota);
                    ti_Write(&g->y, 2, 1, slota);
                    ti_Write(&g->angle, 4, 1, slota);
                    ti_Write(&g->angle, 4, 1, slota);
                    ti_Write(&g->type, 1, 1, slota);
                }
            }
            sprintf(str1, "You created %s.", newPackName);
            ErrorMessage("Success!", str1);

        } else {
            ErrorMessage("Invalid.", "This name is already in use.");
        }
    }
    ti_CloseAll();
}

short findPacks() {
    char *varName;
    uint8_t *searchPos = NULL;
    ti_var_t slot;
    short count = 0;
    ti_CloseAll();
    while ((varName = ti_Detect(&searchPos, search_String)) != NULL) {
        ti_CloseAll();
        if ((slot = ti_Open(varName, "r"))) {
            strcpy(Appvars[count], varName);
            ti_SetArchiveStatus(true, slot);
        }
        ti_CloseAll();
        count++;
        if (count > 10) {
            break;
        }
    }
    return count;
}





void showPacks() {
    uint8_t x;
    ti_var_t slota;
    uint8_t y;
    uint8_t pltile;
    uint8_t tile;
    char str1[] = "this is some buffer text";
    uint8_t plx;
    uint8_t current = 0;
    WhiText();
    y = findPacks();
    x = 30 + (y + 1) * 15;
    pltile = 120 - x / 2;
    while(!(kb_Data[6] & kb_Enter)) {
        kb_Scan();
        gfx_SetColor(0);
        gfx_FillRectangle(40, pltile, 240, x);
        BlaText();
        gfx_SetTextScale(2, 2);
        strcpy(str1, "Select a pack");
        tile = gfx_GetStringWidth(str1);
        gfx_PrintStringXY(str1, 160 - tile / 2, pltile + 5);
        gfx_SetTextScale(1, 1);
        for (plx = 0; plx < y + 1; plx++) {
            if (plx == 0) {
                strcpy(str1, "Create new pack");
            } else {
                strcpy(str1, Appvars[plx - 1]);
            }
            tile = gfx_GetStringWidth(str1);
            gfx_PrintStringXY(str1, 160 - tile / 2, (plx * 15) + pltile + 27);
        }
        if ((kb_Data[7] & kb_Down) && (current < y)) {
            current++;
            while (kb_Data[7] & kb_Down) {
                kb_Scan();
            }
        }
        if ((kb_Data[7] & kb_Up) && (current > 0)) {
            current--;
            while (kb_Data[7] & kb_Up) {
                kb_Scan();
            }
        }
        if (kb_Data[6] & kb_Clear) {
            break;
        }
        gfx_SetColor(7);
        gfx_Rectangle(40, current * 15 + pltile + 24, 240, 14);
        gfx_Rectangle(40, current * 15 + pltile + 25, 240, 12);
        //outside of box
        strcpy(currpackname, Appvars[current - 1]);
        ti_CloseAll();
        slota = ti_Open(currpackname, "r");
        ti_Seek(4, 0, slota);
        ti_Read(&numlevels, 1, 1, slota);
        gfx_SetColor(74);
        gfx_Rectangle(40, pltile, 240, x);
        gfx_Rectangle(41, pltile + 1, 238, x - 2);
        gfx_SetTextBGColor(0);
        gfx_SetTextFGColor(255);
        gfx_SetTextTransparentColor(0);
        if (current == 0) {
            strcpy(str1, "Create new pack");
        } else {
            strcpy(str1, Appvars[current - 1]);
        }
        gfx_SetTextFGColor(7);
        tile = gfx_GetStringWidth(str1);
        gfx_PrintStringXY(str1, 160 - tile / 2, current * 15 + pltile + 27);
        if ((kb_Data[6] & kb_Enter) && (current == 0)) {
            saveAs();
            y = findPacks();
            x = 30 + (y + 1) * 15;
            pltile = 120 - x / 2;
        }
        gfx_SwapDraw();
    }
    while (kb_Data[6] & kb_Enter) {
        kb_Scan();
        gfx_SetColor(255);
        gfx_Rectangle(40, current * 15 + pltile + 24, 240, 14);
        gfx_Rectangle(40, current * 15 + pltile + 25, 240, 12);
        gfx_SetColor(74);
        gfx_Rectangle(40, pltile, 240, x);
        gfx_Rectangle(41, pltile + 1, 238, x - 2);
        gfx_SetTextFGColor(255);
        gfx_PrintStringXY(str1, 160 - tile / 2, (current * 15) + pltile + 27);
        gfx_SwapDraw();
    }
}




/* Put all your code here */
void main(void) {
    short current = 0;
    short levels = 0;
    uint8_t tile = 0;
    uint8_t MapData[14][10];
    gfx_sprite_t *spr;
    gfx_sprite_t *logoa;
    gfx_sprite_t *logob;
    ti_var_t slota;
    ti_var_t slotb;
    uint8_t x = 0;
    uint8_t y = 0;
    uint16_t plx = 0;
    uint16_t ply = 0;
    uint8_t pltile = 0;
    char str1[40];
    bool keypress = true;
    bool currentlyediting = true;
    bool showedpacks = false;
    uint8_t currguard = 0;
    short numguards = 5;
    bool start;
    bool end;
    typedef struct {
        uint8_t type;
        uint16_t x;
        uint16_t y;
        float angle;
        float attangle;
    } guard_t;
    guard_t guard[5];
    ti_CloseAll();
    if (slota = ti_Open("ACRCNMMS","r")) {
        logoa = ti_GetDataPtr(slota);
        ti_Seek(452, 0, slota);
        logob = ti_GetDataPtr(slota);
    }
    gfx_Begin();
    gfx_SetDraw(1);
    gfx_ZeroScreen();
    //main MODE_3_CONTINUOUS
MAINMENU:
    BlaText();
    while((!(kb_Data[6] & kb_Enter)) || (current == 0)) {
        kb_Scan();
        gfx_FillScreen(0);
        gfx_SetColor(255);
        for(x = 0; x < 5; x++) {
            plx = randInt(0, 320);
            ply = randInt(0, 240);
            gfx_SetPixel(plx, ply);
        }
        plx = 0;
        ply = 0;
        gfx_SetTextBGColor(0);
        gfx_SetTextFGColor(255);
        gfx_SetTextTransparentColor(0);
        gfx_SetTransparentColor(255);
        gfx_ScaledTransparentSprite_NoClip(logoa, 70, 5, 3, 2);
        gfx_ScaledTransparentSprite_NoClip(logob, 160, 5, 3, 2);
        for (x = 0; x < 4; x++) {
            if (x == 0) {
                sprintf(str1, "Level < %d / %d >", levels + 1, numlevels);
            }
            if (x == 1) {
                strcpy(str1, "Load");
            }
            if (x == 2) {
                strcpy(str1, "Select pack");
            }
            if (x == 3) {
                strcpy(str1, "Exit");
            }
            y = gfx_GetStringWidth(str1);
            gfx_PrintStringXY(str1, 160 - y / 2, x * 22 + 88);
        }
        if ((kb_Data[7] & kb_Down) && (current < 3) && (keypress)) {
            current++;
            keypress = false;
        }
        if ((kb_Data[7] & kb_Up) && (current > 0) && (keypress)) {
            current--;
            keypress = false;
        }
        if ((kb_Data[7] & kb_Right) && (current == 0) && (levels < numlevels - 1) && (keypress)) {
            levels++;
            keypress = false;
        }
        if ((kb_Data[7] & kb_Left) && (current == 0) && (levels > 0) && (keypress)) {
            levels--;
            keypress = false;
        }
        if (!kb_AnyKey()) {
            keypress = true;
        }
        if (levels + 1 > numlevels) {
            levels = numlevels - 1;
        }
        gfx_SetTextFGColor(7);
        strcpy(str1, "Ace Recon Editor");
        y = gfx_GetStringWidth(str1);
        gfx_PrintStringXY(str1, 160 - y / 2, 35);
        gfx_SetColor(255);
        gfx_FillRectangle(88, 225, 144, 15);
        gfx_FillTriangle(88, 240, 88, 225, 68, 240);
        gfx_FillTriangle(232, 240, 232, 225, 252, 240);
        gfx_SetColor(0);
        gfx_FillRectangle(90, 227, 140, 16);
        gfx_FillTriangle(90, 240, 90, 227, 70, 240);
        gfx_FillTriangle(230, 240, 230, 227, 250, 240);
        gfx_SetTextFGColor(255);
        strcpy(str1, "created by epsilon5");
        y = gfx_GetStringWidth(str1);
        gfx_PrintStringXY(str1, 160 - y / 2, 229);
        gfx_SetColor(7);
        gfx_Rectangle(-2, current * 22 + 85, 324, 14);
        gfx_Rectangle(-2, current * 22 + 86, 324, 12);
        gfx_SetTextBGColor(255);
        gfx_SetTextFGColor(7);
        gfx_SetTextTransparentColor(255);
        if (current == 0) {
            sprintf(str1, "Level < %d / %d >", levels + 1, numlevels);
        }
        if (current == 1) {
            strcpy(str1, "Load");
        }
        if (current == 2) {
            strcpy(str1, "Select pack");
        }
        if (current == 3) {
            strcpy(str1, "Exit");
        }
        y = gfx_GetStringWidth(str1);
        gfx_PrintStringXY(str1, 160 - y / 2, current * 22 + 88);
        if (kb_Data[6] & kb_Enter) {
            gfx_SetTextBGColor(0);
            gfx_SetTextFGColor(255);
            gfx_SetTextTransparentColor(0);
            gfx_SetColor(255);
            gfx_Rectangle(-2, current * 22 + 85, 324, 14);
            gfx_Rectangle(-2, current * 22 + 86, 324, 12);
            gfx_PrintStringXY(str1, 160 - y / 2, current * 22 + 88);
        }
        if (!(showedpacks)) {
            gfx_Blit(1);
            strcpy(currpackname, Appvars[0]);
            showPacks();
            showedpacks = true;
        }
        gfx_SwapDraw();
    }
    while (kb_Data[6] & kb_Enter) {
        kb_Scan();
    }
    if (current == 2) {
        showPacks();
        goto MAINMENU;
    }
    if (current == 3) {
        goto QUIT;
    }
    if (current == 1) {
        for(y = 0; y < 10; ++y) {
            for(x = 0; x < 14; ++x) {
                MapData[x][y] = 0;
            }
        }
        for (x = 0; x < 5; ++x) {
            guard_t *g = &guard[x];
            g->x = 0;
            g->y = 0;
            g->angle = 0;
            g->attangle = 0;
            g->type = 1;
        }
        ti_CloseAll();
        slota = ti_Open(currpackname, "r");
        slotb = ti_Open("ACRCNSPR", "r");
        gfx_FillScreen(0);
        gfx_SetColor(74);
        gfx_Rectangle(4, 19, 282, 202);
        ti_Seek(206 * levels + 5, 0, slota);
        ti_Read(&MapData, 140, 1, slota);
        ti_Read(&numguards, 1, 1, slota);
        ti_Read(&guard, 65, 1, slota);
        gfx_SwapDraw();
        BlaText();
        while (!(kb_Data[6] & kb_Clear)) {
            kb_Scan();
            gfx_ZeroScreen();
            for(y = 0; y < 10; ++y) {
                for(x = 0; x < 14; ++x) {
                    tile = MapData[x][y];
                    if (tile > 10) {
                        MapData[x][y] = 0;
                    }
                    ti_Seek(402 * tile, 0, slotb);
                    spr = ti_GetDataPtr(slotb);
                    gfx_Sprite(spr, x * 20 + 5, y * 20 + 20);
                }
            }
            //text to give people a vague idea of what to do
            gfx_PrintStringXY("[mode]: help", 2, 2);
            if (currentlyediting) {
                gfx_PrintStringXY("-", 2, 230);
                strcpy(str1, "+");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 318 - x, 230);
                strcpy(str1, "Grab");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 80 - x / 2, 230);
                strcpy(str1, "Edit guards >");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 160 - x / 2, 230);
                strcpy(str1, "Fill");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 240 - x / 2, 230);
                sprintf(str1, "Pos: %d, %d", plx, ply);
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 318 - x, 2);
            } else {
                gfx_PrintStringXY("-", 2, 230);
                strcpy(str1, "+");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 318 - x, 230);
                strcpy(str1, "Number");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 80 - x / 2, 230);
                strcpy(str1, "< Edit map");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 160 - x / 2, 230);
                strcpy(str1, "Type");
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 240 - x / 2, 230);
                if (numguards > 0) {
                    sprintf(str1, "Pos: %d, %d", guard[currguard].x, guard[currguard].y);
                } else {
                    strcpy(str1, "Pos: INVALID");
                }
                x = gfx_GetStringWidth(str1);
                gfx_PrintStringXY(str1, 318 - x, 2);
            }
            sprintf(str1, "Name: %s  Lvl: %d", currpackname, levels + 1);
            x = gfx_GetStringWidth(str1);
            gfx_PrintStringXY(str1, 160 - x / 2, 2);
            gfx_SetColor(74);
            gfx_Rectangle(4, 19, 282, 202);
            if (currentlyediting) {
                if ((kb_Data[7] & kb_Up) && (ply > 0)) {
                    ply--;
                    while (kb_Data[7] & kb_Up) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[7] & kb_Right) && (plx < 13)) {
                    plx++;
                    while (kb_Data[7] & kb_Right) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[7] & kb_Left) && (plx > 0)) {
                    plx--;
                    while (kb_Data[7] & kb_Left) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[7] & kb_Down) && (ply < 9)) {
                    ply++;
                    while (kb_Data[7] & kb_Down) {
                        kb_Scan();
                    }
                }
                if (kb_Data[6] & kb_Enter) {
                    MapData[plx][ply] = pltile;
                    while (kb_Data[6] & kb_Enter) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[1] & kb_Yequ) && (pltile > 0)) {
                    pltile--;
                    while (kb_Data[1] & kb_Yequ) {
                        kb_Scan();
                    }
                }
                if (kb_Data[1] & kb_Zoom) {
                    currentlyediting = false;
                    while (kb_Data[1] & kb_Zoom) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[1] & kb_Graph) && (pltile < 10)) {
                    pltile++;
                    while (kb_Data[1] & kb_Graph) {
                        kb_Scan();
                    }
                }
                if (kb_Data[1] & kb_Window) {
                    pltile = MapData[plx][ply];
                }
                if (kb_Data[1] & kb_Trace) {
                    tile = MapData[plx][ply];
                    for(y = 0; y < 10; ++y) {
                        for(x = 0; x < 14; ++x) {
                            if (MapData[x][y] == tile) {
                                MapData[x][y] = pltile;
                            }
                        }
                    }
                }
                if (pltile > 0) {
                    ti_Seek((pltile - 1) * 402, 0, slotb);
                    spr = ti_GetDataPtr(slotb);
                    gfx_Sprite(spr, 300, 120);
                }
                ti_Seek(pltile * 402, 0, slotb);
                spr = ti_GetDataPtr(slotb);
                gfx_Sprite(spr, 299, 140);
                if (pltile < 10) {
                    ti_Seek((pltile + 1) * 402, 0, slotb);
                    spr = ti_GetDataPtr(slotb);
                    gfx_Sprite(spr, 300, 160);
                }
                gfx_SetColor(224);
                gfx_Rectangle(298, 139, 22, 22);
                gfx_Rectangle(plx * 20 + 5, ply * 20 + 20, 20, 20);
                gfx_Rectangle(plx * 20 + 6, ply * 20 + 21, 18, 18);
            } else {
                guard_t *g = &guard[currguard];
                if (kb_Data[1] & kb_Zoom) {
                    currentlyediting = true;
                    while (kb_Data[1] & kb_Zoom) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[1] & kb_Yequ) && (currguard > 0)) {
                    currguard--;
                    while (kb_Data[1] & kb_Yequ) {
                        kb_Scan();
                    }
                }
                if ((kb_Data[1] & kb_Graph) && (currguard < numguards - 1)) {
                    currguard++;
                    while (kb_Data[1] & kb_Graph) {
                        kb_Scan();
                    }
                }
                if (currguard > numguards - 1) {
                    currguard = numguards - 1;
                }
                if (kb_Data[1] & kb_Trace) {
                    gfx_Blit(1);
                    while (!(kb_Data[6] & kb_Enter)) {
                        kb_Scan();
                        gfx_SetColor(0);
                        gfx_FillRectangle(115, 98, 90, 45);
                        gfx_SetColor(74);
                        gfx_Rectangle(115, 98, 90, 45);
                        gfx_Rectangle(116, 99, 88, 43);
                        gfx_SetTextScale(2, 2);
                        strcpy(str1, "Type?");
                        x = gfx_GetStringWidth(str1);
                        gfx_PrintStringXY(str1, 160 - x / 2, 103);
                        gfx_SetTextScale(1, 1);
                        if (g->type == 1) {
                            strcpy(str1, "Patroller >");
                        }
                        if (g->type == 2) {
                            strcpy(str1, "< Chaser >");
                        }
                        if (g->type == 3) {
                            sprintf(str1, "< Sniper");
                        }
                        x = gfx_GetStringWidth(str1);
                        gfx_PrintStringXY(str1, 160 - x / 2, 125);
                        if ((kb_Data[7] & kb_Left) && (g->type > 1)) {
                            g->type--;
                            while (kb_Data[7] & kb_Left) {
                                kb_Scan();
                            }
                        }
                        if ((kb_Data[7] & kb_Right) && (g->type < 3)) {
                            g->type++;
                            while (kb_Data[7] & kb_Right) {
                                kb_Scan();
                            }
                        }
                        gfx_SwapDraw();
                    }
                    while (kb_Data[6] & kb_Enter) {
                        kb_Scan();
                    }
                }
                if (kb_Data[1] & kb_Window) {
                    gfx_Blit(1);
                    while (!(kb_Data[6] & kb_Enter)) {
                        kb_Scan();
                        gfx_SetColor(0);
                        gfx_FillRectangle(115, 98, 90, 45);
                        gfx_SetColor(74);
                        gfx_Rectangle(115, 98, 90, 45);
                        gfx_Rectangle(116, 99, 88, 43);
                        gfx_SetTextScale(2, 2);
                        strcpy(str1, "No.?");
                        x = gfx_GetStringWidth(str1);
                        gfx_PrintStringXY(str1, 160 - x / 2, 103);
                        gfx_SetTextScale(1, 1);
                        sprintf(str1, "< %d >", numguards);
                        x = gfx_GetStringWidth(str1);
                        gfx_PrintStringXY(str1, 160 - x / 2, 125);
                        if ((kb_Data[7] & kb_Left) && (numguards > 0)) {
                            numguards--;
                            while (kb_Data[7] & kb_Left) {
                                kb_Scan();
                            }
                        }
                        if ((kb_Data[7] & kb_Right) && (numguards < 5)) {
                            numguards++;
                            while (kb_Data[7] & kb_Right) {
                                kb_Scan();
                            }
                        }
                        gfx_SwapDraw();
                    }
                    while (kb_Data[6] & kb_Enter) {
                        kb_Scan();
                    }
                }
                if (numguards > 0) {
                    if ((kb_Data[7] & kb_Left) && (g->x > 5)) {
                        g->x--;
                    }
                    if ((kb_Data[7] & kb_Right) && (g->x < 285)) {
                        g->x++;
                    }
                    if ((kb_Data[7] & kb_Up) && (g->y > 20)) {
                        g->y--;
                    }
                    if ((kb_Data[7] & kb_Down) && (g->y < 220)) {
                        g->y++;
                    }
                    if (kb_Data[6] & kb_Add) {
                        g->angle = g->angle + 0.1;
                    }
                    if (kb_Data[6] & kb_Sub) {
                        g->angle = g->angle - 0.1;
                    }
                    if (g->angle > 6.28) {
                        g->angle = 0;
                    }
                    if (g->angle < 0) {
                        g->angle = 6.28;
                    }
                    if (g->x > 285) {
                        g->x = 285;
                    }
                    if (g->x < 5) {
                        g->x = 5;
                    }
                    if (g->y > 220) {
                        g->y = 220;
                    }
                    if (g->y < 20) {
                        g->y = 20;
                    }
                    gfx_SetColor(7);
                    gfx_Circle(g->x, g->y, 7);
                    gfx_Circle(g->x, g->y, 8);
                    gfx_SetColor(224);
                    for (x = 0; x < numguards; ++x) {
                        guard_t *g = &guard[x];
                        g->attangle = g->angle;
                        gfx_FillCircle(g->x, g->y, 5);
                        gfx_Line(g->x + 15 * cos(g->angle), g->y + 15 * sin(g->angle), g->x, g->y);
                    }
                }
            }
            gfx_SwapDraw();
        }
        ti_CloseAll();
        start = false;
        end = false;
        slota = ti_Open(currpackname, "r+");
        for(y = 0; y < 10; ++y) {
            for(x = 0; x < 14; ++x) {
                tile = MapData[x][y];
                if (tile == 5) {
                    start = true;
                }
                if (tile == 6) {
                    end = true;
                }
            }
        }
        if (start && end) {
            start = true;
        } else {
            start = false;
        }
        if (slota) {
            ti_Seek(206 * levels + 5, 0, slota);
            ti_Write(&MapData, 140, 1, slota);
            ti_Write(&numguards, 1, 1, slota);
            ti_Write(&guard, 65, 1, slota);
            ti_SetArchiveStatus(1, slota);
        }
        if (kb_Data[6] & kb_Clear) {
            goto MAINMENU;
        }
    }
QUIT:
    gfx_End();
}

