/*
 * parser.c
 *
 *  Created on: Apr 26, 2019
 *      Author: user
 */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

/***USER_INCLUDES***/
/*start*/
#include "debug.h"
#include "types_def.h"
#include "parser.h"
#include "ruuvi_endpoint_ca_uart.h"
/*end*/

/***USER_VARIABLES***/
/*start*/
api_callbacks_fn_t parser_callback_func_tbl_null ={
    .ApiAckCallback     = NULL,
    .ApiReportCallback  = NULL,
};

api_callbacks_fn_t *p_parser_callback_func_tbl =
        &parser_callback_func_tbl_null;
/*end*/

/***USER_STATIC_FUNCTIONS***/
/*start*/
/*end*/
int parse_callbacks_unreg()
{
    print_dbgmsg("Enter\n");
    p_parser_callback_func_tbl = &parser_callback_func_tbl_null;
    print_dbgmsg("End\n");
    return 0;
}

int parse_callbacks_reg(void *p_callback)
{
    int res=0;
    print_dbgmsg("Enter\n");
    if ((api_callbacks_fn_t *)p_callback != NULL)
        p_parser_callback_func_tbl = (api_callbacks_fn_t *)p_callback;
    else{
        print_errmsg("%d nullptr,\n", __LINE__);
        res=(-1);
    }
    print_dbgmsg("End\n");
    return res;
}

int parse(__u8 *buffer) {
    switch (buffer[RE_CA_UART_CMD_INDEX])
    {
        case RE_CA_UART_ACK:
            p_parser_callback_func_tbl->ApiAckCallback(buffer);
            break;
        case RE_CA_UART_ADV_RPRT:
            p_parser_callback_func_tbl->ApiReportCallback(buffer);
            break;

        default:
            break;
    }
    return 0;
}
