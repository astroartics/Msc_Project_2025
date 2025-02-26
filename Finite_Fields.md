## Finite Fields in Cryptography

- GF(p): A finite field with a prime number p of elements. The elements of GF(p) are the integers {0,1,2,…,p−1}, and the arithmetic is performed modulo p.
- GF(p^n): A finite field with p^n elements, where p is a prime number and n is a positive integer. These fields are often used in elliptic curve cryptography (ECC) or when constructing more complex cryptosystems.

- Mathematical Structure: Finite fields provide a well-defined and predictable mathematical structure for cryptographic algorithms. They ensure that every element (except 0) has a multiplicative inverse, which is essential for many cryptographic protocols.
- Elliptic Curve Cryptography (ECC): ECC relies on arithmetic over finite fields, typically GF(p) or GF(p^n), to create secure cryptographic systems with smaller keys than other methods like RSA (Rivest-Shamir-Adleman, a public-key cryptography algorithm).
- Security: The difficulty of solving certain problems in finite fields, like the discrete logarithm problem (DLP), is the foundation of the security of many cryptographic systems. For example, both RSA and Diffie-Hellman key exchange algorithms rely on operations in finite fields and the hardness of the DLP.

#### Peculiar properties
- A finite field is closed under the operations of addition, subtraction, multiplication, and division (except by zero). This means that performing these operations on any two elements in the finite field will always result in an element that is also in the field.
- The set of elements in a finite field behaves much like the rational numbers or real numbers under standard arithmetic, but with the crucial distinction that there are only a finite number of elements.
- Additive Inverses: For every element a in the field, there exists an element −a such that a+(−a)=0. This is true even in finite fields, where the additive inverse of an element is found by subtracting the element modulo the field size.
- Multiplicative Inverses: Every element except zero has a multiplicative inverse. That is, for each element a != 0, there exists an element a^(−1) such that a⋅a^(−1) = 1. This property is essential in cryptography for operations such as modular division.
- p times any element equals 0, i.e., p⋅a = 0 for all elements a. (For example, if p = 5 and elements in field = {0,1,2,3,4} then (5*1) mod 5 = 0, (5*3) mod 5 = 0 i.e. 15%5 = 0, and so on).

#### Modular division
> It is the process of dividing one number by another in modular arithmetic
<div align="center">
<img src="https://github.com/user-attachments/assets/ca448d68-d7be-47e7-b7e8-61a19498064a">
</div>  

#### Order of an element
> The order of an element a in a finite field is the smallest positive integer k such that: a^k = 1
<div align="center">
<img src="https://github.com/user-attachments/assets/ec8e4775-cf83-46dc-94eb-d05b9843e2a1"><br/>
<img src="https://github.com/user-attachments/assets/b369355f-066b-4b2e-89c5-4357343b0322">
</div>  

#### Cyclic structure
<div align="center">
<img src="https://github.com/user-attachments/assets/8f562797-5cf2-4ae2-bbee-aa0fa5253fba">
</div>  
