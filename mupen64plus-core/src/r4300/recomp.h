/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - recomp.h                                                *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2002 Hacktarux                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef M64P_R4300_RECOMP_H
#define M64P_R4300_RECOMP_H

#include <stdint.h>

#if defined(__LIBRETRO_WIN64__)
#define __x86_64__
#endif

#include <stddef.h>
#include "hacktarux_dynarec/assemble_struct.h"

typedef struct _precomp_instr
{
   void (*ops)(void);
   union
     {
    struct
      {
         long long int *rs;
         long long int *rt;
         int16_t immediate;
      } i;
    struct
      {
         uint32_t inst_index;
      } j;
    struct
      {
         long long int *rs;
         long long int *rt;
         long long int *rd;
         unsigned char sa;
         unsigned char nrd;
      } r;
    struct
      {
         unsigned char base;
         unsigned char ft;
         short offset;
      } lf;
    struct
      {
         unsigned char ft;
         unsigned char fs;
         unsigned char fd;
      } cf;
     } f;
   uint32_t addr; /* word-aligned instruction address in r4300 address space */
   unsigned int local_addr; /* byte offset to start of corresponding x86_64 instructions, from start of code block */
   reg_cache_struct reg_cache_infos;
} precomp_instr;

typedef struct _precomp_block
{
   precomp_instr *block;
   uint32_t start;
   uint32_t end;
   unsigned char *code;
   unsigned int code_length;
   unsigned int max_code_length;
   void *jumps_table;
   int jumps_number;
   void *riprel_table;
   int riprel_number;
   unsigned int adler32;
} precomp_block;

void recompile_block(const uint32_t *source, precomp_block *block, uint32_t func);
void init_block(precomp_block *block);
void free_block(precomp_block *block);
void recompile_opcode(void);
void dyna_jump(void);
void dyna_start(void *code);
void dyna_stop(void);
void *realloc_exec(void *ptr, size_t oldsize, size_t newsize);

extern precomp_instr *dst; /* precomp_instr structure for instruction being recompiled */

extern int no_compiled_jump;

#ifdef DYNAREC
#include "hacktarux_dynarec/assemble.h"
#endif
#include "hacktarux_dynarec/regcache.h"

#endif /* M64P_R4300_RECOMP_H */
