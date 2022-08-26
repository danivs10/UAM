/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#define N_CMDT 2
#define N_CMD 19


/*Kinds of CMD that the user can input*/
typedef enum enum_CmdType {
  CMDS, 
  CMDL} T_CmdType;

/*Different inputs that are accepted and have a functionality*/
typedef enum enum_Command {
  NO_CMD = -1, 
  UNKNOWN, 
  EXIT, 
  NEXT, 
  BACK,
  TAKE, 
  DROP,
  ROLL,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  MOVE,
  INSPECT,
  TURNON,
  TURNOFF,
  OPENWITH,
  SAVE,
  LOAD} T_Command;

T_Command get_user_input(char* argument, char* with, char* linkName);

#endif
