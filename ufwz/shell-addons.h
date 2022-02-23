#ifndef INC_SHELL_ADDONS_H
#define INC_SHELL_ADDONS_H

#include <stdarg.h>

#include <c/register-table.h>

void ufw_shell_fprintf(void*, const char*, ...);
void ufw_shell_reg_init(RegisterTable*);

#endif /* INC_SHELL_ADDONS_H */
