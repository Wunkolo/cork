
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
