inp w       // w = data[0]
mul x 0     // x = 0
add x z     // x = 0
mod x 26    // x = 0
div z 1     // z = 0
add x 10    // x = 10
eql x w     // x = 0
eql x 0     // x = 1
mul y 0     // y = 0
add y 25    // y = 25
mul y x     // y = 25
add y 1     // y = 26
mul z y     // z =  0
mul y 0     // y = 0
add y w     // y = data[0]
add y 0     // y = data[0]
mul y x     // y = data[0]
add z y     // z = data[0]

// w=data[0], x=1, y=data[0], z=data[0]

inp w       // w = data[1]
mul x 0     // x = 0
add x z     // x = data[0]
mod x 26    // x = data[0] % 26
div z 1     // z = z
add x 12    // x = (data[0] % 26) + 12
eql x w     // x = (((data[0] % 26) + 12) == data[1])
eql x 0     // x = (((data[0] % 26) + 12) != data[1])
mul y 0     // y = 0
add y 25    // y = 25
mul y x     // y = (((data[0] % 26) + 12) != data[1]) ? 25 : 0
add y 1     // y = (((data[0] % 26) + 12) != data[1]) ? 26 : 1
mul z y     // z = z * ((((data[0] % 26) + 12) != data[1]) ? 26 : 1)
mul y 0     // y = 0
add y w     // y = data[1]
add y 6     // y = data[1] + 6
mul y x     // y = (data[1] + 6) * (((data[0] % 26) + 12) != data[1])
add z y     // z = (data[0] * ((25 * (((data[0] % 26) + 12) != data[1])) + 1)) + (data[1] + 6) * (((data[0] % 26) + 12) != data[1])
// w=data[1], x=(((data[0] % 26) + 12) != data[1]), y=(data[1] + 6) * (((data[0] % 26) + 12) != data[1]), z = (data[0] * ((25 * (((data[0] % 26) + 12) != data[1])) + 1)) + (data[1] + 6) * (((data[0] % 26) + 12) != data[1])


inp w       // w = data[2]
mul x 0     // x = 0
add x z     // x = (data[0] * ((25 * (((data[0] % 26) + 12) != data[1])) + 1)) + (data[1] + 6) * (((data[0] % 26) + 12) != data[1])
mod x 26    // x = res % 26
div z 1     // 
add x 13
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 4
mul y x
add z y     // z = z * ((((z % 26) + 13) != data[]) ? 26 : 1) + ((data[] + 4) * ((z % 26) + 13))

inp w
mul x 0
add x z
mod x 26
div z 1
add x 13
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 2
mul y x
add z y     // z = z * ((((z % 26) + 13) != data[]) ? 26 : 1) + ((data[] + 2) * ((z % 26) + 13))

inp w
mul x 0
add x z
mod x 26
div z 1
add x 14
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 9
mul y x
add z y     // z = z * ((((z % 26) + 14) != data[]) ? 26 : 1) + ((data[] + 9) * ((z % 26) + 14))

inp w
mul x 0
add x z
mod x 26
div z 26
add x -2
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 1
mul y x
add z y     // z = (z / 26) * ((((z % 26) - 2) != data[]) ? 26 : 1) + ((data[] + 1) * ((z % 26) - 2))

inp w
mul x 0
add x z
mod x 26
div z 1
add x 11
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 10
mul y x
add z y     // z = z * ((((z % 26) + 11) != data[]) ? 26 : 1) + ((data[] + 10) * ((z % 26) + 11))

inp w
mul x 0
add x z
mod x 26
div z 26
add x -15
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 6
mul y x
add z y     // z = (z / 26) * ((((z % 26) - 15) != data[]) ? 26 : 1) + ((data[] + 6) * ((z % 26) - 15))

inp w
mul x 0
add x z
mod x 26
div z 26
add x -10
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 4
mul y x
add z y     // z = (z / 26) * ((((z % 26) - 10) != data[]) ? 26 : 1) + ((data[] + 4) * ((z % 26) - 10))

inp w
mul x 0
add x z
mod x 26
div z 1
add x 10
eql x w
eql x 0
mul y 0
add y 25
mul y x
add y 1
mul z y
mul y 0
add y w
add y 6
mul y x
add z y     // z = z * ((((z % 26) + 10) != data[]) ? 26 : 1) + ((data[] + 6) * ((z % 26) + 10))

inp w       // w = data[]
mul x 0     // x = 0
add x z     // x = z
mod x 26    // x = (z % 26)
div z 26    // z = (z / 26)
add x -10   // x = (z % 26) - 10
eql x w     // x = ((z % 26) - 10) == data[]
eql x 0     // x = ((z % 26) - 10) != data[]
mul y 0     // y = 0
add y 25    // y = 25
mul y x     // y = (((z % 26) - 10) != data[]) ? 25 : 0
add y 1     // y = ((((z % 26) - 10) != data[]) ? 25 : 0) + 1
mul z y     // z = (z / 26) * (((((z % 26) - 10) != data[]) ? 25 : 0) + 1)
mul y 0     // y = 0
add y w     // y = data[]
add y 3     // y = data[] + 3
mul y x     // y = (data[] + 3) * ((z % 26) - 10)
add z y     // z = (z / 26) * (((((z % 26) - 10) != data[]) ? 25 : 0) + 1) + ((data[] + 3) * ((z % 26) - 10))

inp w       // w = data[]
mul x 0     // x = 0
add x z     // x = z
mod x 26    // x = (z % 26)
div z 26    // z = (z / 26)
add x -4    // x = (z % 26) - 4
eql x w     // x = ((z % 26) - 4) == data[]
eql x 0     // x = ((z % 26) - 4) != data[]
mul y 0     // y = 0
add y 25    // y = 25
mul y x     // y = (((z % 26) - 4) != data[]) ? 25 : 0
add y 1     // y = ((((z % 26) - 4) != data[]) ? 25 : 0) + 1
mul z y     // z = (z / 26) * (((((z % 26) - 4) != data[]) ? 25 : 0) + 1)
mul y 0     // y = 0
add y w     // y = data[]
add y 9     // y = data[] + 9
mul y x     // y = (data[] + 9) * ((z % 26) - 4)
add z y     // z = ((z / 26) * (((((z % 26) - 4) != data[]) ? 25 : 0) + 1)) + ((data[] + 9) * ((z % 26) - 4))
add z y     // z = ((z / 26) * ((((z % 26) - 4) != data[]) ? 26 : 1)) + ((((z % 26) - 4) != data[]) ? (data[] + 15) : 0)

inp w       // w = data[]
mul x 0     // x = 0
add x z     // x = z
mod x 26    // x = (z % 26)
div z 26    // z = (z / 26)
add x -1    // x = (z % 26) + 1
eql x w     // x = ((z % 26) + 1) == data[]
eql x 0     // x = ((z % 26) + 1) != data[]
mul y 0     // y = 0
add y 25    // y = 25
mul y x     // y = (((z % 26) + 1) != data[]) ? 25 : 0
add y 1     // y = ((((z % 26) + 1) != data[]) ? 25 : 0) + 1
mul z y     // z = (z / 26) * (((((z % 26) + 1) != data[]) ? 25 : 0) + 1)
mul y 0     // y = 0
add y w     // y = data[]
add y 15    // y = data[] + 15
mul y x     // y = (data[] + 15) * ((z % 26) + 1)
add z y     // z = ((z / 26) * ((((z % 26) + 1) != data[]) ? 26 : 1)) + ((((z % 26) + 1) != data[]) ? (data[] + 15) : 0)

inp w       // w = data[]
mul x 0     // x = 0
add x z     // x = z
mod x 26    // x = (z % 26)
div z 26    // z = (z / 26)
add x -1    // x = (z % 26) - 1
eql x w     // x = (((z % 26) - 1) == data[])
eql x 0     // x = (((z % 26) - 1) != data[])
mul y 0     // y = 0
add y 25    // y = 25
mul y x     // y = (((z % 26) - 1) != data[]) ? 25 : 0
add y 1     // y = (((z % 26) - 1) != data[]) ? 26 : 1
mul z y     // z = (z / 26) * ((((z % 26) - 1) != data[]) ? 26 : 1)
mul y 0     // y = 0
add y w     // y = data[]
add y 5     // y = data[] + 5
mul y x     // y = (((z % 26) - 1) != data[]) ? (data[] + 5) : 0
add z y     // z = ((z / 26) * ((((z % 26) - 1) != data[]) ? 26 : 1)) + ((((z % 26) - 1) != data[]) ? (data[] + 5) : 0)
            // z = (((z % 26) - 1) != data[]) ? (z - (z % 26)) : (z / 26)) + ((((z % 26) - 1) == data[]) ? 0 : (data[] + 5))


int64_t f(int64_t z, int64_t data, int64_t divisor, int64_t mod_add, int64_t res_add) {
    int64_t div = z / divisor;
    int64_t mod = z % 26;

    int64_t res = 0;

    if ((mod + mod_add) != data) {
        res = div * 26 + data + res_add;
    } else {
        res = div;
    }

    return res;
}