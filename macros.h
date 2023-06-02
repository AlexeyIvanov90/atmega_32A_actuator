/*
 * macros.h
 *
 * Created: 11.09.2014 17:00:09
 *  Author: Roma
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define _arg8(_0,_1,_2,_3,_4,_5,_6,_7,_8,...) _8
#define _args_count(...) _arg8( __VA_ARGS__ , 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1 )

#define _ppcat_nx(a,b) a ## b
#define _ppcat(a,b) _ppcat_nx(a,b)

#define _mask8(BIT,...) (1 << BIT) | _mask7(__VA_ARGS__)
#define _mask7(BIT,...) (1 << BIT) | _mask6(__VA_ARGS__)
#define _mask6(BIT,...) (1 << BIT) | _mask5(__VA_ARGS__)
#define _mask5(BIT,...) (1 << BIT) | _mask4(__VA_ARGS__)
#define _mask4(BIT,...) (1 << BIT) | _mask3(__VA_ARGS__)
#define _mask3(BIT,...) (1 << BIT) | _mask2(__VA_ARGS__)
#define _mask2(BIT,...) (1 << BIT) | _mask1(__VA_ARGS__)
#define _mask1(BIT) (1 << BIT)

#define _set_bit2(PORT,BIT) PORT |= (1 << BIT)
#define _set_bit1(...) _set_bit2 __VA_ARGS__
#define set_bit(...) _set_bit1((__VA_ARGS__))

#define set_bits(PORT,...) PORT |= (  _ppcat(_mask , _args_count(__VA_ARGS__))(__VA_ARGS__)  )

#define _clr_bit2(PORT,BIT) PORT &= (~(1 << BIT))
#define _clr_bit1(...) _clr_bit2 __VA_ARGS__
#define clr_bit(...) _clr_bit1((__VA_ARGS__))

#define clr_bits(PORT,...) PORT &= (~(  _ppcat(_mask , _args_count(__VA_ARGS__))(__VA_ARGS__)  ))

#define _inv_bit2(PORT,BIT) PORT ^= (1 << BIT)
#define _inv_bit1(...) _inv_bit2 __VA_ARGS__
#define inv_bit(...) _inv_bit1((__VA_ARGS__))

#define inv_bits(PORT,...) PORT ^= ( _ppcat(_mask , _args_count(__VA_ARGS__))(__VA_ARGS__) )

#define _bit2(PORT,BIT) (PORT & (1 << BIT))
#define _bit1(...) _bit2 __VA_ARGS__
#define bit(...) _bit1((__VA_ARGS__))

#define _notbit2(PORT,BIT) ( !(PORT & (1 << BIT)))
#define _notbit1(...) _notbit2 __VA_ARGS__
#define notbit(...) _notbit1((__VA_ARGS__))

#define set_only_bits(PORT,...) PORT = (  _ppcat(_mask , _args_count(__VA_ARGS__))(__VA_ARGS__)  )

#endif /* MACROS_H_ */