/*
 * This file was automatically generated using arm64-pgtable-tool.
 * See: https:@github.com/ashwio/arm64-pgtable-tool
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This code programs the following translation table structure:
 *
 *         level 1 table @ 0x200000
 *         [@   0]-------------------------\
 *                 level 2 table @ 0x201000
 *                 [@   0] 0x000000000000-0x0000001fffff, RW_Data, RAM
 *
 * The following command line arguments were passed to arm64-pgtable-tool:
 *
 *      -i examples/base-fvp-comp310.txt
 *      -ttb 0x200000
 *      -el 1
 *      -tg 4K
 *      -tsz 32
 *
 * This memory map requires a total of 2 translation tables.
 * Each table occupies 4K of memory (0x1000 bytes).
 * The buffer pointed to by 0x200000 must therefore be 2x 4K = 0x2000 bytes long.
 * It is the programmer's responsibility to guarantee this.
 *
 * The programmer must also ensure that the virtual memory region containing the
 * translation tables is itself marked as NORMAL in the memory map file.
 */

    .section .data.mmu
    .balign 2

    mmu_lock: .4byte 0
    #define LOCKED 1

    mmu_init: .4byte 0
    #define INITIALISED 1

    .section .text.mmu_on
    .balign 2
    .global mmu_on
    .type mmu_on, @function

mmu_on:

    ADRP    x0, mmu_lock
    ADD     x0, x0, :lo12:mmu_lock
    MOV     w1, #LOCKED
    SEVL
1:
    WFE
    LDAXR   w2, [x0]
    CBNZ    w2, 1b
    STXR    w3, w1, [x0]
    CBNZ    w3, 1b

check_already_initialised:

    ADRP    x1, mmu_init
    ADD     x1, x1, :lo12:mmu_init
    LDR     w2, [x1]
    CBNZ    w2, end

zero_out_tables:

    LDR     x2, =0x200000
    LDR     x3, =0x2000
    LSR     x3, x3, #5
    FMOV    d0, xzr
1:
    STP     q0, q0, [x2], #32
    SUBS    x3, x3, #1
    B.NE    1b

load_descriptor_templates:

    LDR     x2, =0x20000000000705
    LDR     x3, =0x20000000000707
    LDR     x4, =0x20000000000701
    LDR     x5, =0x20000000000703
    LDR     x20, =0x781
    LDR     x21, =0x783


program_table_0:

    LDR     x8, =0x200000
    LDR     x9, =0x40000000

program_table_0_entry_0:

    LDR     x10, =0
    LDR     x11, =0x201000
    ORR     x11, x11, #0x3
    STR     x11, [x8, x10, lsl #3]
program_table_1:

    LDR     x8, =0x201000
    LDR     x9, =0x200000

program_table_1_entry_0:

    LDR     x10, =0
    LDR     x11, =1
    LDR     x12, =0x0
1:
    ORR     x12, x12, x4
    STR     X12, [x8, x10, lsl #3]
    ADD     x10, x10, #1
    ADD     x12, x12, x9
    SUBS    x11, x11, #1
    B.NE    1b

init_done:

    MOV     w2, #INITIALISED
    STR     w2, [x1]

end:

    LDR     x1, =0x200000
    MSR     ttbr0_el1, x1
    LDR     x1, =0xff
    MSR     mair_el1, x1
    LDR     x1, =0x803520
    MSR     tcr_el1, x1
    ISB
    MRS     x2, tcr_el1
    CMP     x2, x1
    B.NE    .
    LDR     x1, =0x1005
    MSR     sctlr_el1, x1
    ISB
    STLR    wzr, [x0]
    RET
