/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Daniel Varela and Aran Rodrigo
 * @version 2.0 
 * @date 13-01-2020 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include "command.h"

#define CMD_LENGHT 30

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e","Exit"}, {"n", "Next"}, {"b","Back"}, {"t","Take"}, {"d","Drop"}, {"rl","Roll"}, {"l","Left"}, {"r","Right"}, {"u","Up"}, {"dn","Down"}, {"m","Move"}, {"i","Inspect"}, {"ton","turnon"}, {"toff","turnoff"}, {"o", "open"},  {"s", "save"},  {"l", "load"}};


/*
This function detects what you input in the game and returns the necessary cmd according to the input
*/
T_Command get_user_input(char* argument, char* with, char* linkName){

    T_Command cmd = NO_CMD;
    char input[CMD_LENGHT] = "";
    int i = UNKNOWN - NO_CMD + 1;
    if (scanf("%s", input) > 0){
        cmd = UNKNOWN;
	while(cmd == UNKNOWN && i < N_CMD){
            if (!strcasecmp(input, cmd_to_str[i][CMDS])|| 
                !strcasecmp(input, cmd_to_str[i][CMDL])){
                cmd = i + NO_CMD;
	    }
            else{
		    i++;
            }
        }
    }

    if(cmd == TAKE || cmd == DROP || cmd == INSPECT || cmd == MOVE || cmd == TURNON || cmd == TURNOFF){
        scanf("%s", argument);
        linkName[0] = '\0';
        with[0] = '\0';

    }else if (cmd == OPENWITH){
        scanf("%s", linkName);
        scanf("%s", with);
        scanf("%s", argument);

    }else{
        argument[0] = '\0';
        linkName[0] = '\0';
        with[0] = '\0';
    }

    return cmd;
}
