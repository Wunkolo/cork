
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