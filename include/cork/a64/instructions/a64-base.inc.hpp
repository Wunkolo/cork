
/// @brief ADC - Add with Carry adds two register values and the Carry flag
/// value, and writes the result to the destination register.
/// @note ADC_32_addsub_carry
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
void ADC(WReg Wd, WReg Wn, WReg Wm)
{
	Emit<"00011010000mmmmm000000nnnnnddddd", "d", "n", "m">(Wd, Wn, Wm);
}

/// @brief ADC - Add with Carry adds two register values and the Carry flag
/// value, and writes the result to the destination register.
/// @note ADC_64_addsub_carry
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
void ADC(XReg Xd, XReg Xn, XReg Xm)
{
	Emit<"10011010000mmmmm000000nnnnnddddd", "d", "n", "m">(Xd, Xn, Xm);
}

/// @brief ADCS - Add with Carry, setting flags, adds two register values and
/// the Carry flag value, and writes the result to the destination register. It
/// updates the condition flags based on the result.
/// @note ADCS_32_addsub_carry
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
void ADCS(WReg Wd, WReg Wn, WReg Wm)
{
	Emit<"00111010000mmmmm000000nnnnnddddd", "d", "n", "m">(Wd, Wn, Wm);
}

/// @brief ADCS - Add with Carry, setting flags, adds two register values and
/// the Carry flag value, and writes the result to the destination register. It
/// updates the condition flags based on the result.
/// @note ADCS_64_addsub_carry
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
void ADCS(XReg Xd, XReg Xn, XReg Xm)
{
	Emit<"10111010000mmmmm000000nnnnnddddd", "d", "n", "m">(Xd, Xn, Xm);
}

/// @brief B - Branch causes an unconditional branch to a label at a PC-relative
/// offset, with a hint that this is not a subroutine call or return.
/// @note B_only_branch_imm
/// @param label Is the program label to be unconditionally branched to. Its
/// offset from the address of this instruction, in the range +/-128MB, is
/// encoded as "imm26" times 4.
void B(SImm<26, 4> label)
{
	Emit<"000101iiiiiiiiiiiiiiiiiiiiiiiiii", "i">(label);
}

/// @brief B - Branch conditionally to a label at a PC-relative offset, with a
/// hint that this is not a subroutine call or return.
/// @note B_only_condbranch
/// @param cond Is one of the standard conditions
/// @param label Is the program label to be conditionally branched to. Its
/// offset from the address of this instruction, in the range +/-1MB, is encoded
/// as "imm19" times 4.
void B(Condition cond, SImm<19, 4> label)
{
	Emit<"01010100iiiiiiiiiiiiiiiiiii0cccc", "i", "c">(label, cond);
}

/// @brief BLR - Branch with Link to Register calls a subroutine at an address
/// in a register, setting register X30 to PC+4.
/// @note BLR_64_branch_reg
/// @param Xn Is the 64-bit name of the general-purpose register holding the
/// address to be branched to, encoded in the "Rn" field.
void BLR(XReg Xn)
{
	Emit<"1101011000111111000000nnnnn00000", "n">(Xn);
}

/// @brief BR - Branch to Register branches unconditionally to an address in a
/// register, with a hint that this is not a subroutine return.
/// @note BR_64_branch_reg
/// @param Xn Is the 64-bit name of the general-purpose register holding the
/// address to be branched to, encoded in the "Rn" field.
void BR(XReg Xn)
{
	Emit<"1101011000011111000000nnnnn00000", "n">(Xn);
}

/// @brief BRK - Breakpoint instruction. A BRK instruction generates a
/// Breakpoint Instruction exception. The PE records the exception in ESR_ELx,
/// using the EC value 0x3C, and captures the value of the immediate argument in
/// ESR_ELx.ISS. Within a guarded memory region, while PSTATE.BTYPE != 0b00, a
/// BRK instruction will not generate a Branch Target Exception and will
/// generate a Breakpoint Instruction exception as normal. For more information,
/// see PSTATE.BTYPE.
/// @note BRK_EX_exception
/// @param imm Is a 16-bit unsigned immediate, in the range 0 to 65535, encoded
/// in the "imm16" field.
void BRK(Imm<16> imm)
{
	Emit<"11010100001iiiiiiiiiiiiiiii00000", "i">(imm);
}

/// @brief CBNZ - Compare and Branch on Nonzero compares the value in a register
/// with zero, and conditionally branches to a label at a PC-relative offset if
/// the comparison is not equal. It provides a hint that this is not a
/// subroutine call or return. This instruction does not affect the condition
/// flags.
/// @note CBNZ_32_compbranch
/// @param Wt Is the 32-bit name of the general-purpose register to be tested,
/// encoded in the "Rt" field.
/// @param label Is the program label to be conditionally branched to. Its
/// offset from the address of this instruction, in the range +/-1MB, is encoded
/// as "imm19" times 4.
void CBNZ(WReg Wt, SImm<19, 4> label)
{
	Emit<"00110101iiiiiiiiiiiiiiiiiiittttt", "t", "i">(Wt, label);
}

/// @brief CBNZ - Compare and Branch on Nonzero compares the value in a register
/// with zero, and conditionally branches to a label at a PC-relative offset if
/// the comparison is not equal. It provides a hint that this is not a
/// subroutine call or return. This instruction does not affect the condition
/// flags.
/// @note CBNZ_64_compbranch
/// @param Xt Is the 64-bit name of the general-purpose register to be tested,
/// encoded in the "Rt" field.
/// @param label Is the program label to be conditionally branched to. Its
/// offset from the address of this instruction, in the range +/-1MB, is encoded
/// as "imm19" times 4.
void CBNZ(XReg Xt, SImm<19, 4> label)
{
	Emit<"10110101iiiiiiiiiiiiiiiiiiittttt", "t", "i">(Xt, label);
}

/// @brief CBZ - Compare and Branch on Zero compares the value in a register
/// with zero, and conditionally branches to a label at a PC-relative offset if
/// the comparison is equal. It provides a hint that this is not a subroutine
/// call or return. This instruction does not affect condition flags.
/// @note CBZ_32_compbranch
/// @param Wt Is the 32-bit name of the general-purpose register to be tested,
/// encoded in the "Rt" field.
/// @param label Is the program label to be conditionally branched to. Its
/// offset from the address of this instruction, in the range +/-1MB, is encoded
/// as "imm19" times 4.
void CBZ(WReg Wt, SImm<19, 4> label)
{
	Emit<"00110100iiiiiiiiiiiiiiiiiiittttt", "t", "i">(Wt, label);
}

/// @brief CBZ - Compare and Branch on Zero compares the value in a register
/// with zero, and conditionally branches to a label at a PC-relative offset if
/// the comparison is equal. It provides a hint that this is not a subroutine
/// call or return. This instruction does not affect condition flags.
/// @note CBZ_64_compbranch
/// @param Xt Is the 64-bit name of the general-purpose register to be tested,
/// encoded in the "Rt" field.
/// @param label Is the program label to be conditionally branched to. Its
/// offset from the address of this instruction, in the range +/-1MB, is encoded
/// as "imm19" times 4.
void CBZ(XReg Xt, SImm<19, 4> label)
{
	Emit<"10110100iiiiiiiiiiiiiiiiiiittttt", "t", "i">(Xt, label);
}

/// @brief CCMN - Conditional Compare Negative (immediate) sets the value of the
/// condition flags to the result of the comparison of a register value and a
/// negated immediate value if the condition is TRUE, and an immediate value
/// otherwise.
/// @note CCMN_32_condcmp_imm
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param imm Is a five bit unsigned (positive) immediate encoded in the "imm5"
/// field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMN(WReg Wn, Imm<5> imm, ConditionFlag nzcv, Condition cond)
{
	Emit<"00111010010iiiiicccc10nnnnn0ffff", "n", "i", "f", "c">(
		Wn, imm, nzcv, cond
	);
}

/// @brief CCMN - Conditional Compare Negative (immediate) sets the value of the
/// condition flags to the result of the comparison of a register value and a
/// negated immediate value if the condition is TRUE, and an immediate value
/// otherwise.
/// @note CCMN_64_condcmp_imm
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param imm Is a five bit unsigned (positive) immediate encoded in the "imm5"
/// field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMN(XReg Xn, Imm<5> imm, ConditionFlag nzcv, Condition cond)
{
	Emit<"10111010010iiiiicccc10nnnnn0ffff", "n", "i", "f", "c">(
		Xn, imm, nzcv, cond
	);
}

/// @brief CCMN - Conditional Compare Negative (register) sets the value of the
/// condition flags to the result of the comparison of a register value and the
/// inverse of another register value if the condition is TRUE, and an immediate
/// value otherwise.
/// @note CCMN_32_condcmp_reg
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMN(WReg Wn, WReg Wm, ConditionFlag nzcv, Condition cond)
{
	Emit<"00111010010mmmmmcccc00nnnnn0ffff", "n", "m", "f", "c">(
		Wn, Wm, nzcv, cond
	);
}

/// @brief CCMN - Conditional Compare Negative (register) sets the value of the
/// condition flags to the result of the comparison of a register value and the
/// inverse of another register value if the condition is TRUE, and an immediate
/// value otherwise.
/// @note CCMN_64_condcmp_reg
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMN(XReg Xn, XReg Xm, ConditionFlag nzcv, Condition cond)
{
	Emit<"10111010010mmmmmcccc00nnnnn0ffff", "n", "m", "f", "c">(
		Xn, Xm, nzcv, cond
	);
}

/// @brief CCMP - Conditional Compare (immediate) sets the value of the
/// condition flags to the result of the comparison of a register value and an
/// immediate value if the condition is TRUE, and an immediate value otherwise.
/// @note CCMP_32_condcmp_imm
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param imm Is a five bit unsigned (positive) immediate encoded in the "imm5"
/// field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMP(WReg Wn, Imm<5> imm, ConditionFlag nzcv, Condition cond)
{
	Emit<"01111010010iiiiicccc10nnnnn0ffff", "n", "i", "f", "c">(
		Wn, imm, nzcv, cond
	);
}

/// @brief CCMP - Conditional Compare (immediate) sets the value of the
/// condition flags to the result of the comparison of a register value and an
/// immediate value if the condition is TRUE, and an immediate value otherwise.
/// @note CCMP_64_condcmp_imm
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param imm Is a five bit unsigned (positive) immediate encoded in the "imm5"
/// field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMP(XReg Xn, Imm<5> imm, ConditionFlag nzcv, Condition cond)
{
	Emit<"11111010010iiiiicccc10nnnnn0ffff", "n", "i", "f", "c">(
		Xn, imm, nzcv, cond
	);
}

/// @brief CCMP - Conditional Compare (register) sets the value of the condition
/// flags to the result of the comparison of two registers if the condition is
/// TRUE, and an immediate value otherwise.
/// @note CCMP_32_condcmp_reg
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMP(WReg Wn, WReg Wm, ConditionFlag nzcv, Condition cond)
{
	Emit<"01111010010mmmmmcccc00nnnnn0ffff", "n", "m", "f", "c">(
		Wn, Wm, nzcv, cond
	);
}

/// @brief CCMP - Conditional Compare (register) sets the value of the condition
/// flags to the result of the comparison of two registers if the condition is
/// TRUE, and an immediate value otherwise.
/// @note CCMP_64_condcmp_reg
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param nzcv Is the flag bit specifier, an immediate in the range 0 to 15,
/// giving the alternative state for the 4-bit NZCV condition flags, encoded in
/// the "nzcv" field.
/// @param cond Is one of the standard conditions, encoded in the standard way.
void CCMP(XReg Xn, XReg Xm, ConditionFlag nzcv, Condition cond)
{
	Emit<"11111010010mmmmmcccc00nnnnn0ffff", "n", "m", "f", "c">(
		Xn, Xm, nzcv, cond
	);
}

/// @brief CINC - Conditional Increment returns, in the destination register,
/// the value of the source register incremented by 1 if the condition is TRUE,
/// and otherwise returns the value of the source register.
/// @note CINC_CSINC_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" and "Rm" fields.
/// @param cond Is one of the standard conditions, excluding AL and NV,
/// encoded with its least significant bit inverted.
void CINC(WReg Wd, WReg Wn, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"00011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wn, invcond
	);
}

/// @brief CINC - Conditional Increment returns, in the destination register,
/// the value of the source register incremented by 1 if the condition is TRUE,
/// and otherwise returns the value of the source register.
/// @note CINC_CSINC_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" and "Rm" fields.
/// @param cond Is one of the standard conditions, excluding AL and NV,
/// encoded with its least significant bit inverted.
void CINC(XReg Xd, XReg Xn, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"10011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xn, invcond
	);
}

/// @brief CINV - Conditional Invert returns, in the destination register, the
/// bitwise inversion of the value of the source register if the condition is
/// TRUE, and otherwise returns the value of the source register.
/// @note CINV_CSINV_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" and "Rm" fields.
/// @param cond Is one of the standard conditions, excluding AL and NV,
/// encoded with its least significant bit inverted.
void CINV(WReg Wd, WReg Wn, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"01011010100mmmmmcccc00nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wn, invcond
	);
}

/// @brief CINV - Conditional Invert returns, in the destination register, the
/// bitwise inversion of the value of the source register if the condition is
/// TRUE, and otherwise returns the value of the source register.
/// @note CINV_CSINV_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" and "Rm" fields.
/// @param cond Is one of the standard conditions, excluding AL and NV,
/// encoded with its least significant bit inverted.
void CINV(XReg Xd, XReg Xn, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"11011010100mmmmmcccc00nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xn, invcond
	);
}

/// @brief CLREX - Clear Exclusive clears the local monitor of the executing PE.
/// @note CLREX_BN_barriers
/// @param imm Is an optional 4-bit unsigned immediate, in the range 0 to 15,
/// defaulting to 15 and encoded in the "CRm" field.
void CLREX(Imm<4> imm = 0b1111)
{
	Emit<"11010101000000110011MMMM01011111", "M">(imm);
}

/// @brief CLS - Count Leading Sign bits counts the number of leading bits of
/// the source register that have the same value as the most significant bit of
/// the register, and writes the result to the destination register. This count
/// does not include the most significant bit of the source register.
/// @note CLS_32_dp_1src
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void CLS(WReg Wd, WReg Wn)
{
	Emit<"0101101011000000000101nnnnnddddd", "d", "n">(Wd, Wn);
}

/// @brief CLS - Count Leading Sign bits counts the number of leading bits of
/// the source register that have the same value as the most significant bit of
/// the register, and writes the result to the destination register. This count
/// does not include the most significant bit of the source register.
/// @note CLS_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void CLS(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000101nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief CLZ - Count Leading Zeros counts the number of consecutive binary
/// zero bits, starting from the most significant bit in the source register,
/// and places the count in the destination register.
/// @note CLZ_32_dp_1src
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void CLZ(WReg Wd, WReg Wn)
{
	Emit<"0101101011000000000100nnnnnddddd", "d", "n">(Wd, Wn);
}

/// @brief CLZ - Count Leading Zeros counts the number of consecutive binary
/// zero bits, starting from the most significant bit in the source register,
/// and places the count in the destination register.
/// @note CLZ_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void CLZ(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000100nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief CMN - Compare Negative (extended register) adds a register value and
/// a sign or zero-extended register value, followed by an optional left shift
/// amount. The argument that is extended from the <Rm> register can be a byte,
/// halfword, word, or doubleword. It updates the condition flags based on the
/// result, and discards the result.
/// @note CMN_ADDS_32S_addsub_ext
/// @param Wn Is the 32-bit name of the first source general-purpose register or
/// stack pointer, encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param extend For the 32-bit variant: is the extension to be applied to the
/// second source operand.
/// @param amount Is the left shift amount to be applied after extension in the
/// range 0 to 4, defaulting to 0, encoded in the "imm3" field. It must be
/// absent when <extend> is absent, is required when <extend> is LSL, and is
/// optional when <extend> is present but not LSL.
void CMN(WRegWsp Wn, WReg Wm, RegisterExtension extend, Imm<3> amount = 0)
{
	// TODO: Allow "LSL" as extension argument
	assert(amount.Value <= 4);
	Emit<"00101011001mmmmmxxxiiinnnnn11111", "n", "m", "x", "i">(
		Wn, Wm, extend, amount
	);
}

/// @brief CMN - Compare Negative (extended register) adds a register value and
/// a sign or zero-extended register value, followed by an optional left shift
/// amount. The argument that is extended from the <Rm> register can be a byte,
/// halfword, word, or doubleword. It updates the condition flags based on the
/// result, and discards the result.
/// @note CMN_ADDS_64S_addsub_ext
/// @param Xn Is the 64-bit name of the first source general-purpose register or
/// stack pointer, encoded in the "Rn" field.
/// @param Rm Is the number [0-30] of the second general-purpose source register
/// or the name ZR (31), encoded in the "Rm" field.
/// @param extend For the 64-bit variant: is the extension to be applied to the
/// second source operand.
/// @param amount Is the left shift amount to be applied after extension in the
/// range 0 to 4, defaulting to 0, encoded in the "imm3" field. It must be
/// absent when <extend> is absent, is required when <extend> is LSL, and is
/// optional when <extend> is present but not LSL.
void CMN(XRegSp Xn, RReg Rm, RegisterExtension extend, Imm<3> amount = 0)
{
	// TODO: Allow "LSL" as extension argument
	// TODO: Verify extension with Rm width
	assert(amount.Value <= 4);
	Emit<"10101011001mmmmmxxxiiinnnnn11111", "n", "m", "x", "i">(
		Xn, Rm, extend, amount
	);
}

/// @brief CMN - Compare Negative (immediate) adds a register value and an
/// optionally-shifted immediate value. It updates the condition flags based on
/// the result, and discards the result.
/// @note CMN_ADDS_32S_addsub_imm
/// @param Wn Is the 32-bit name of the source general-purpose register or stack
/// pointer, encoded in the "Rn" field.
/// @param imm Is an unsigned immediate, in the range 0 to 4095, encoded in the
/// "imm12" field.
/// @param shift Is the optional left shift to apply to the immediate,
/// defaulting to 0.
void CMN(WRegWsp Wn, Imm<12> imm, LslOnly, ImmChoice<0, 12> shift = 0)
{
	Emit<"001100010siiiiiiiiiiiinnnnn11111", "n", "i", "s">(Wn, imm, shift);
}

/// @brief CMN - Compare Negative (immediate) adds a register value and an
/// optionally-shifted immediate value. It updates the condition flags based on
/// the result, and discards the result.
/// @note CMN_ADDS_64S_addsub_imm
/// @param Xn Is the 64-bit name of the source general-purpose register or stack
/// pointer, encoded in the "Rn" field.
/// @param imm Is an unsigned immediate, in the range 0 to 4095, encoded in the
/// "imm12" field.
/// @param shift Is the optional left shift to apply to the immediate,
/// defaulting to 0.
void CMN(XRegSp Xn, Imm<12> imm, LslOnly, ImmChoice<0, 12> shift = 0)
{
	Emit<"101100010siiiiiiiiiiiinnnnn11111", "n", "i", "s">(Xn, imm, shift);
}

/// @brief CMN - Compare Negative (shifted register) adds a register value and
/// an optionally-shifted register value. It updates the condition flags based
/// on the result, and discards the result.
/// @note CMN_ADDS_32_addsub_shift
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param shift Is the optional shift type to be applied to the second source
/// operand, defaulting to LSL.
/// @param amount For the 32-bit variant: is the shift amount, in the range 0 to
/// 31, defaulting to 0 and encoded in the "imm6" field.
void CMN(WReg Wn, WReg Wm, Shift shift = LSL, Imm<6> amount = 0)
{
	assert(amount.Value <= 31);
	Emit<"00101011ss0mmmmmiiiiiinnnnn11111", "n", "m", "s", "i">(
		Wn, Wm, shift, amount
	);
}

/// @brief CMN - Compare Negative (shifted register) adds a register value and
/// an optionally-shifted register value. It updates the condition flags based
/// on the result, and discards the result.
/// @note CMN_ADDS_64_addsub_shift
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param shift Is the optional shift type to be applied to the second source
/// operand, defaulting to LSL.
/// @param amount For the 64-bit variant: is the shift amount, in the range 0 to
/// 63, defaulting to 0 and encoded in the "imm6" field.
void CMN(XReg Xn, XReg Xm, Shift shift = LSL, Imm<6> amount = 0)
{
	Emit<"10101011ss0mmmmmiiiiiinnnnn11111", "n", "m", "s", "i">(
		Xn, Xm, shift, amount
	);
}

/// @brief CMP - Compare (extended register) subtracts a sign or zero-extended
/// register value, followed by an optional left shift amount, from a register
/// value. The argument that is extended from the <Rm> register can be a byte,
/// halfword, word, or doubleword. It updates the condition flags based on the
/// result, and discards the result.
/// @note CMP_SUBS_32S_addsub_ext
/// @param Wn Is the 32-bit name of the first source general-purpose register or
/// stack pointer, encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param extend For the 32-bit variant: is the extension to be applied to the
/// second source operand.
/// @param amount Is the left shift amount to be applied after extension in the
/// range 0 to 4, defaulting to 0, encoded in the "imm3" field. It must be
/// absent when <extend> is absent, is required when <extend> is
/// LSL, and is optional when <extend> is present but not LSL.
void CMP(WRegWsp Wn, WReg Wm, RegisterExtension extend, Imm<3> amount = 0)
{
	// TODO: Allow "LSL" as extension argument
	assert(amount.Value <= 4);
	Emit<"01101011001mmmmmxxxiiinnnnn11111", "n", "m", "x", "i">(
		Wn, Wm, extend, amount
	);
}

/// @brief CMP - Compare (extended register) subtracts a sign or zero-extended
/// register value, followed by an optional left shift amount, from a register
/// value. The argument that is extended from the <Rm> register can be a byte,
/// halfword, word, or doubleword. It updates the condition flags based on the
/// result, and discards the result.
/// @note CMP_SUBS_64S_addsub_ext
/// @param Xn Is the 64-bit name of the first source general-purpose register or
/// stack pointer, encoded in the "Rn" field.
/// @param Rm Is the number [0-30] of the second general-purpose source register
/// or the name ZR (31), encoded in the "Rm" field.
/// @param extend For the 64-bit variant: is the extension to be applied to the
/// second source operand.
/// @param amount Is the left shift amount to be applied after extension in the
/// range 0 to 4, defaulting to 0, encoded in the "imm3" field. It must be
/// absent when <extend> is absent, is required when <extend> is
/// LSL, and is optional when <extend> is present but not LSL.
void CMP(XRegSp Xn, RReg Rm, RegisterExtension extend, Imm<3> amount = 0)
{
	// TODO: Allow "LSL" as extension argument
	// TODO: Verify extension with Rm width
	assert(amount.Value <= 4);
	Emit<"11101011001mmmmmxxxiiinnnnn11111", "n", "m", "x", "i">(
		Xn, Rm, extend, amount
	);
}

/// @brief CMP - Compare (immediate) subtracts an optionally-shifted immediate
/// value from a register value. It updates the condition flags based on the
/// result, and discards the result.
/// @note CMP_SUBS_32S_addsub_imm
/// @param Wn Is the 32-bit name of the source general-purpose register or stack
/// pointer, encoded in the "Rn" field.
/// @param imm Is an unsigned immediate, in the range 0 to 4095, encoded in the
/// "imm12" field.
/// @param shift Is the optional left shift to apply to the immediate,
/// defaulting to 0.
void CMP(WRegWsp Wn, Imm<12> imm, LslOnly, ImmChoice<0, 12> shift = 0)
{
	Emit<"011100010siiiiiiiiiiiinnnnn11111", "n", "i", "s">(Wn, imm, shift);
}

/// @brief CMP - Compare (immediate) subtracts an optionally-shifted immediate
/// value from a register value. It updates the condition flags based on the
/// result, and discards the result.
/// @note CMP_SUBS_64S_addsub_imm
/// @param Xn Is the 64-bit name of the source general-purpose register or stack
/// pointer, encoded in the "Rn" field.
/// @param imm Is an unsigned immediate, in the range 0 to 4095, encoded in the
/// "imm12" field.
/// @param shift Is the optional left shift to apply to the immediate,
/// defaulting to 0.
void CMP(XRegSp Xn, Imm<12> imm, LslOnly, ImmChoice<0, 12> shift = 0)
{
	Emit<"111100010siiiiiiiiiiiinnnnn11111", "n", "i", "s">(Xn, imm, shift);
}

/// @brief CMP - Compare (shifted register) subtracts an optionally-shifted
/// register value from a register value. It updates the condition flags based
/// on the result, and discards the result.
/// @note CMP_SUBS_32_addsub_shift
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param shift Is the optional shift type to be applied to the second source
/// operand, defaulting to LSL.
/// @param amount For the 32-bit variant: is the shift amount, in the range 0 to
/// 31, defaulting to 0 and encoded in the "imm6" field.
void CMP(WReg Wn, WReg Wm, Shift shift = LSL, Imm<6> amount = 0)
{
	assert(amount.Value <= 31);
	Emit<"01101011ss0mmmmmiiiiiinnnnn11111", "n", "m", "s", "i">(
		Wn, Wm, shift, amount
	);
}

/// @brief CMP - Compare (shifted register) subtracts an optionally-shifted
/// register value from a register value. It updates the condition flags based
/// on the result, and discards the result.
/// @note CMP_SUBS_64_addsub_shift
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param shift Is the optional shift type to be applied to the second source
/// operand, defaulting to LSL.
/// @param amount For the 64-bit variant: is the shift amount, in the range 0 to
/// 63, defaulting to 0 and encoded in the "imm6" field.
void CMP(XReg Xn, XReg Xm, Shift shift = LSL, Imm<6> amount = 0)
{
	assert(amount.Value <= 63);
	Emit<"11101011ss0mmmmmiiiiiinnnnn11111", "n", "m", "s", "i">(
		Xn, Xm, shift, amount
	);
}

/// @brief CNEG - Conditional Negate returns, in the destination register, the
/// negated value of the source register if the condition is TRUE, and otherwise
/// returns the value of the source register.
/// @note CNEG_CSNEG_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" and "Rm" fields.
/// @param cond Is one of the standard conditions, excluding AL and NV,
/// encoded with its least significant bit inverted.
void CNEG(WReg Wd, WReg Wn, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"01011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wn, invcond
	);
}

/// @brief CNEG - Conditional Negate returns, in the destination register, the
/// negated value of the source register if the condition is TRUE, and otherwise
/// returns the value of the source register.
/// @note CNEG_CSNEG_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" and "Rm" fields.
/// @param cond Is one of the standard conditions, excluding AL and NV,
/// encoded with its least significant bit inverted.
void CNEG(XReg Xd, XReg Xn, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"11011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xn, invcond
	);
}

/// @brief CSDB - Consumption of Speculative Data Barrier is a memory barrier
/// that controls speculative execution arising from data value prediction. For
/// more information and details of the semantics, see Consumption of
/// Speculative Data Barrier (CSDB).
/// @note CSDB_HI_hints
void CSDB()
{
	Emit<"11010101000000110010001010011111">();
}

/// @brief CSEL - If the condition is true, Conditional Select writes the value
/// of the first source register to the destination register. If the condition
/// is false, it writes the value of the second source register to the
/// destination register.
/// @note CSEL_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSEL(WReg Wd, WReg Wn, WReg Wm, Condition cond)
{
	Emit<"00011010100mmmmmcccc00nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wm, cond
	);
}

/// @brief CSEL - If the condition is true, Conditional Select writes the value
/// of the first source register to the destination register. If the condition
/// is false, it writes the value of the second source register to the
/// destination register.
/// @note CSEL_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSEL(XReg Xd, XReg Xn, XReg Xm, Condition cond)
{
	Emit<"10011010100mmmmmcccc00nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xm, cond
	);
}

/// @brief CSET - Conditional Set sets the destination register to 1 if the
/// condition is TRUE, and otherwise sets it to 0.
/// @note CSET_CSINC_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param cond Is one of the standard conditions, excluding AL and NV, encoded
/// with its least significant bit inverted.
void CSET(WReg Wd, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"0001101010011111cccc0111111ddddd", "d", "c">(Wd, invcond);
}

/// @brief CSET - Conditional Set sets the destination register to 1 if the
/// condition is TRUE, and otherwise sets it to 0.
/// @note CSET_CSINC_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param cond Is one of the standard conditions, excluding AL and NV, encoded
/// with its least significant bit inverted.
void CSET(XReg Xd, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"1001101010011111cccc0111111ddddd", "d", "c">(Xd, invcond);
}

/// @brief CSETM - Conditional Set Mask sets all bits of the destination
/// register to 1 if the condition is TRUE, and otherwise sets all bits to 0.
/// @note CSETM_CSINV_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param cond Is one of the standard conditions, excluding AL and NV, encoded
/// with its least significant bit inverted.
void CSETM(WReg Wd, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"0101101010011111cccc0011111ddddd", "d", "c">(Wd, invcond);
}

/// @brief CSETM - Conditional Set Mask sets all bits of the destination
/// register to 1 if the condition is TRUE, and otherwise sets all bits to 0.
/// @note CSETM_CSINV_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param cond Is one of the standard conditions, excluding AL and NV, encoded
/// with its least significant bit inverted.
void CSETM(XReg Xd, Condition cond)
{
	assert(cond != Condition::AL);
	assert(cond != Condition::NV);
	const Condition invcond = Invert(cond);
	Emit<"1101101010011111cccc0011111ddddd", "d", "c">(Xd, invcond);
}

/// @brief CSINC - Conditional Select Increment returns, in the destination
/// register, the value of the first source register if the condition is TRUE,
/// and otherwise returns the value of the second source register incremented
/// by 1.
/// @note CSINC_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSINC(WReg Wd, WReg Wn, WReg Wm, Condition cond)
{
	Emit<"00011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wm, cond
	);
}

/// @brief CSINC - Conditional Select Increment returns, in the destination
/// register, the value of the first source register if the condition is TRUE,
/// and otherwise returns the value of the second source register incremented
/// by 1.
/// @note CSINC_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSINC(XReg Xd, XReg Xn, XReg Xm, Condition cond)
{
	Emit<"10011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xm, cond
	);
}

/// @brief CSINV - Conditional Select Invert returns, in the destination
/// register, the value of the first source register if the condition is TRUE,
/// and otherwise returns the bitwise inversion value of the second source
/// register.
/// @note CSINV_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSINV(WReg Wd, WReg Wn, WReg Wm, Condition cond)
{
	Emit<"01011010100mmmmmcccc00nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wm, cond
	);
}

/// @brief CSINV - Conditional Select Invert returns, in the destination
/// register, the value of the first source register if the condition is TRUE,
/// and otherwise returns the bitwise inversion value of the second source
/// register.
/// @note CSINV_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSINV(XReg Xd, XReg Xn, XReg Xm, Condition cond)
{
	Emit<"11011010100mmmmmcccc00nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xm, cond
	);
}

/// @brief CSNEG - Conditional Select Negation returns, in the destination
/// register, the value of the first source register if the condition is TRUE,
/// and otherwise returns the negated value of the second source register.
/// @note CSNEG_32_condsel
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Wm Is the 32-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSNEG(WReg Wd, WReg Wn, WReg Wm, Condition cond)
{
	Emit<"01011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Wd, Wn, Wm, cond
	);
}

/// @brief CSNEG - Conditional Select Negation returns, in the destination
/// register, the value of the first source register if the condition is TRUE,
/// and otherwise returns the negated value of the second source register.
/// @note CSNEG_64_condsel
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the first general-purpose source register,
/// encoded in the "Rn" field.
/// @param Xm Is the 64-bit name of the second general-purpose source register,
/// encoded in the "Rm" field.
/// @param cond Is one of the standard conditions.
void CSNEG(XReg Xd, XReg Xn, XReg Xm, Condition cond)
{
	Emit<"11011010100mmmmmcccc01nnnnnddddd", "d", "n", "m", "c">(
		Xd, Xn, Xm, cond
	);
}

/// @brief DCPS1 - Debug Change PE State to EL1, when executed in Debug state:
/// The target exception level of a DCPS1 instruction is: When the target
/// Exception level of a DCPS1 instruction is ELx, on executing this
/// instruction: This instruction is UNDEFINED at EL0 in Non-secure state if EL2
/// is implemented and HCR_EL2.TGE == 1. This instruction is always UNDEFINED in
/// Non-debug state.
/// @note DCPS1_DC_exception
/// @param imm Is an optional 16-bit unsigned immediate, in the range 0 to
/// 65535, defaulting to 0 and encoded in the "imm16" field.
void DCPS1(Imm<16> imm)
{
	Emit<"11010100101iiiiiiiiiiiiiiii00001", "i">(imm);
}

/// @brief DCPS2 - Debug Change PE State to EL2, when executed in Debug state:
/// The target exception level of a DCPS2 instruction is: When the target
/// Exception level of a DCPS2 instruction is ELx, on executing this
/// instruction: This instruction is UNDEFINED at the following exception
/// levels: This instruction is always UNDEFINED in Non-debug state.
/// @note DCPS2_DC_exception
/// @param imm Is an optional 16-bit unsigned immediate, in the range 0 to
/// 65535, defaulting to 0 and encoded in the "imm16" field.
void DCPS2(Imm<16> imm)
{
	Emit<"11010100101iiiiiiiiiiiiiiii00010", "i">(imm);
}

/// @brief DCPS3 - Debug Change PE State to EL3, when executed in Debug state:
/// The target exception level of a DCPS3 instruction is EL3. On executing a
/// DCPS3 instruction: This instruction is UNDEFINED at all exception levels if
/// either: This instruction is always UNDEFINED in Non-debug state.
/// @note DCPS3_DC_exception
/// @param imm Is an optional 16-bit unsigned immediate, in the range 0 to
/// 65535, defaulting to 0 and encoded in the "imm16" field.
void DCPS3(Imm<16> imm)
{
	Emit<"11010100101iiiiiiiiiiiiiiii00011", "i">(imm);
}

/// @brief DMB - Data Memory Barrier is a memory barrier that ensures the
/// ordering of observations of memory accesses.
/// @note DMB_BO_barriers
/// @param option Specifies the limitation on the barrier operation
void DMB(BarrierOperation option)
{
	Emit<"11010101000000110011MMMM10111111", "M">(option);
}

/// @brief DRPS - Debug restore PE state using the SPSR for the current
/// Exception level. When executed, the PE restores PSTATE from the SPSR. The PE
/// checks the SPSR for the current Exception level for an illegal return event.
/// See Illegal return events from AArch64 state. This instruction is UNDEFINED
/// at EL0. This instruction is UNDEFINED in Non-debug state.
/// @note DRPS_64E_branch_reg
void DRPS()
{
	Emit<"11010110101111110000001111100000">();
}

/// @brief ERET - Exception Return using the ELR and SPSR for the current
/// Exception level. When executed, the PE restores PSTATE from the SPSR, and
/// branches to the address held in the ELR. The PE checks the SPSR for the
/// current Exception level for an illegal return event. See Illegal return
/// events from AArch64 state. ERET is UNDEFINED at EL0.
/// @note ERET_64E_branch_reg
void ERET()
{
	Emit<"11010110100111110000001111100000">();
}

/// @brief HLT - Halt instruction. An HLT instruction can generate a Halt
/// Instruction debug event, which causes entry into Debug state. Within a
/// guarded memory region, while PSTATE.BTYPE != 0b00, a HLT instruction that
/// would cause entry into Debug state will not generate a Branch Target
/// Exception and will cause entry into Debug state as normal. For more
/// information, see PSTATE.BTYPE.
/// @note HLT_EX_exception
/// @param imm Is a 16-bit unsigned immediate, in the range 0 to 65535, encoded
/// in the "imm16" field.
void HLT(Imm<16> imm)
{
	Emit<"11010100010iiiiiiiiiiiiiiii00000", "i">(imm);
}

/// @brief HVC - Hypervisor Call causes an exception to EL2. Software executing
/// at EL1 can use this instruction to call the hypervisor to request a service.
/// The HVC instruction is UNDEFINED: On executing an HVC instruction, the PE
/// records the exception as a Hypervisor Call exception in ESR_ELx, using the
/// EC value 0x16, and the value of the immediate argument.
/// @note HVC_EX_exception
/// @param imm Is a 16-bit unsigned immediate, in the range 0 to 65535, encoded
/// in the "imm16" field.
void HVC(Imm<16> imm)
{
	Emit<"11010100000iiiiiiiiiiiiiiii00010", "i">(imm);
}

/// @brief IC - Instruction Cache operation.
/// @note IC_SYS_CR_systeminstrs
/// @param ic Is an IC operation name.
/// @param Xt Is the 64-bit name of the optional general-purpose source
/// register, defaulting to '11111', encoded in the "Rt" field.
void IC(InstructionCacheOperation ic, XReg Xt = XZR)
{
	Emit<"1101010100001ooo0111MMMMooottttt", "oMo", "t">(ic, Xt);
}

/// @brief ISB - Instruction Synchronization Barrier flushes the pipeline in the
/// PE and is a context synchronization event. For more information, see
/// Instruction Synchronization Barrier (ISB).
/// @note ISB_BI_barriers
/// @param option Specifies an optional limitation on the barrier operation.
void ISB(BarrierOperation option = BarrierOperation::SY)
{
	Emit<"11010101000000110011MMMM11011111", "M">(option);
}

/// @brief NOP - No Operation does nothing, other than advance the value of the
/// program counter by 4. This instruction can be used for instruction alignment
/// purposes.
/// @note NOP_HI_hints
void NOP()
{
	Emit<"11010101000000110010000000011111">();
}

/// @brief RBIT - Reverse Bits reverses the bit order in a register.
/// @note RBIT_32_dp_1src
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void RBIT(WReg Wd, WReg Wn)
{
	Emit<"0101101011000000000000nnnnnddddd", "d", "n">(Wd, Wn);
}

/// @brief RBIT - Reverse Bits reverses the bit order in a register.
/// @note RBIT_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void RBIT(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000000nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief RET - Return from subroutine branches unconditionally to an address
/// in a register, with a hint that this is a subroutine return.
/// @note RET_64R_branch_reg
/// @param Xn Is the 64-bit name of the general-purpose register holding the
/// address to be branched to, encoded in the "Rn" field. Defaults to X30 if
/// absent.
void RET(XReg Xn)
{
	Emit<"1101011001011111000000nnnnn00000", "n">(Xn);
}

/// @brief REV - Reverse Bytes reverses the byte order in a register.
/// @note REV_32_dp_1src
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void REV(WReg Wd, WReg Wn)
{
	Emit<"0101101011000000000010nnnnnddddd", "d", "n">(Wd, Wn);
}

/// @brief REV - Reverse Bytes reverses the byte order in a register.
/// @note REV_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void REV(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000011nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief REV16 - Reverse bytes in 16-bit halfwords reverses the byte order in
/// each 16-bit halfword of a register.
/// @note REV16_32_dp_1src
/// @param Wd Is the 32-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Wn Is the 32-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void REV16(WReg Wd, WReg Wn)
{
	Emit<"0101101011000000000001nnnnnddddd", "d", "n">(Wd, Wn);
}

/// @brief REV16 - Reverse bytes in 16-bit halfwords reverses the byte order in
/// each 16-bit halfword of a register.
/// @note REV16_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void REV16(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000001nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief REV32 - Reverse bytes in 32-bit words reverses the byte order in each
/// 32-bit word of a register.
/// @note REV32_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void REV32(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000010nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief REV64 - Reverse Bytes reverses the byte order in a 64-bit
/// general-purpose register. When assembling for Armv8.2, an assembler must
/// support this pseudo-instruction. It is OPTIONAL whether an assembler
/// supports this pseudo-instruction when assembling for an architecture earlier
/// than Armv8.2.
/// @note REV64_REV_64_dp_1src
/// @param Xd Is the 64-bit name of the general-purpose destination register,
/// encoded in the "Rd" field.
/// @param Xn Is the 64-bit name of the general-purpose source register, encoded
/// in the "Rn" field.
void REV64(XReg Xd, XReg Xn)
{
	Emit<"1101101011000000000011nnnnnddddd", "d", "n">(Xd, Xn);
}

/// @brief SMC - Secure Monitor Call causes an exception to EL3. SMC is
/// available only for software executing at EL1 or higher. It is UNDEFINED in
/// EL0. If the values of HCR_EL2.TSC and SCR_EL3.SMD are both 0, execution of
/// an SMC instruction at EL1 or higher generates a Secure Monitor Call
/// exception, recording it in ESR_ELx, using the EC value 0x17, that is taken
/// to EL3. If the value of HCR_EL2.TSC is 1 and EL2 is enabled in the current
/// Security state, execution of an SMC instruction at EL1 generates an
/// exception that is taken to EL2, regardless of the value of SCR_EL3.SMD. If
/// the value of HCR_EL2.TSC is 0 and the value of SCR_EL3.SMD is 1, the SMC
/// instruction is UNDEFINED.
/// @note SMC_EX_exception
/// @param imm Is a 16-bit unsigned immediate, in the range 0 to 65535, encoded
/// in the "imm16" field.
void SMC(Imm<16> imm)
{
	Emit<"11010100000iiiiiiiiiiiiiiii00011", "i">(imm);
}

/// @brief SVC - Supervisor Call causes an exception to be taken to EL1. On
/// executing an SVC instruction, the PE records the exception as a Supervisor
/// Call exception in ESR_ELx, using the EC value 0x15, and the value of the
/// immediate argument.
/// @note SVC_EX_exception
/// @param imm Is a 16-bit unsigned immediate, in the range 0 to 65535, encoded
/// in the "imm16" field.
void SVC(Imm<16> imm)
{
	Emit<"11010100000iiiiiiiiiiiiiiii00001", "i">(imm);
}

/// @brief UDF - Permanently Undefined generates an Undefined Instruction
/// exception (ESR_ELx.EC = 0b000000). The encodings for UDF used in this
/// section are defined as permanently UNDEFINED.
/// @note UDF_only_perm_undef
/// @param imm is a 16-bit unsigned immediate, in the range 0 to 65535, encoded
/// in the "imm16" field. The PE ignores the value of this constant.
void UDF(Imm<16> imm)
{
	Emit<"0000000000000000iiiiiiiiiiiiiiii", "i">(imm);
}

/// @brief WFE - Wait For Event is a hint instruction that indicates that the PE
/// can enter a low-power state and remain there until a wakeup event occurs.
/// Wakeup events include the event signaled as a result of executing the SEV
/// instruction on any PE in the multiprocessor system. For more information,
/// see Wait For Event mechanism and Send event. As described in Wait For Event
/// mechanism and Send event, the execution of a WFE instruction that would
/// otherwise cause entry to a low-power state can be trapped to a higher
/// Exception level.
/// @note WFE_HI_hints
void WFE()
{
	Emit<"11010101000000110010000001011111">();
}

/// @brief WFI - Wait For Interrupt is a hint instruction that indicates that
/// the PE can enter a low-power state and remain there until a wakeup event
/// occurs. For more information, see Wait For Interrupt. As described in Wait
/// For Interrupt, the execution of a WFI instruction that would otherwise cause
/// entry to a low-power state can be trapped to a higher Exception level.
/// @note WFI_HI_hints
void WFI()
{
	Emit<"11010101000000110010000001111111">();
}

/// @brief YIELD - YIELD is a hint instruction. Software with a multithreading
/// capability can use a YIELD instruction to indicate to the PE that it is
/// performing a task, for example a spin-lock, that could be swapped out to
/// improve overall system performance. The PE can use this hint to suspend and
/// resume multiple software threads if it supports the capability. For more
/// information about the recommended use of this instruction, see The YIELD
/// instruction.
/// @note YIELD_HI_hints
void YIELD()
{
	Emit<"11010101000000110010000000111111">();
}
