
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
