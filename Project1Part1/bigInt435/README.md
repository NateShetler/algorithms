Nathaniel Shetler
ID: 4015423
Class: Algorithms

# Project1Part1 (rsa435.cc file):

## Functions:

### fermatTest:
This function is an implementation of fermat's test. The function will accept in a BigUnsigned number.
The function will then check to see if the number passed in is prime or not. It does this by using the 
modexp function. The modexp function is used by passing the the base (first time called is 2, second time 
called is 5), the exponent (number passed in - 1), and the number. If the modexp function returns 1, then 
the number is probably prime. If it returns anything else the number is not prime. This function is called 
twice to be nearly certain that the number passed in is prime. The function will return a boolean, true or 
false, depending on the results of the modexp function calls. True if the number is prime, false if the number
is not prime. 

### createPrime:
This function will create a prime number and return it. This function creates a random BigUnsigned number that 
is 155 digits, and then will pass it into the fermatTest function to determine if the number is prime. If the 
number is prime then it will return the number, if it isn't then it will create a new random number and check it
with fermats test until a prime one is found. 

### generateE:
This function will accept in the phi of n value and e value created in main. This function will set the e value.
The e is started at 151. It will then call extendedEuclidean algorithm and keeps track of the divisor (third parameter
passed to extendedEuclidean function). If the divisor equals 1, then e is set and the function finishes. If the 
divisor is not 1, 2 will be added to e. This process will continue until divisor equals 1.

#### main:
First, the three files are opened. These files are p_q.txt, e_n.txt, d_n.txt. Then p and q are create by calling the
createPrime function. During this process, p and q are written to the p_q.txt file. Next, n is calculated (p*q) and then 
phi of n is calculated ((p-1) * (q-1)). Next, e is created and set by the generateE function. Then e and n are are written
to the e_n.txt file. Following this, d is created using the modinv function by passing e and phiOfn to the function. D and 
n are then written to the d_n.txt file. Lastly, the files are all closed. 




## Project1Part2 (sign.cc file):

During this part of the project, the program will allow you to sign the document with a digital signature
or verify a signed document to see if it is valid or if it has been modified. 

### Signing a file:
To accomplish this, the sha256 function will be used to generate a hash value for the content of a given 
file (file.txt). After the sha256 value is obtained, it is converted to a BigUnsigned number using the BigUnsignedInABase
function. Next, the d and n values are taken from the d_n.txt file and converted to BigUnsigned numbers. Now, the
digital signature is created (the hash value is decryted) using the modexp function by passing in the hash value
number, d number, and n number. Now the signature file is created if it hasnt't been created before. The digital 
signature is then written to the signature file. The program outputs that the file has been signed, and then the files
are closed.   

To run this part of the program the user will need to type: ./sign s file.txt

### Verifying a file:
First, the d_n.txt and e_n.txt files are opened and the e, d, and n values are read from the file and 
then converted to BigUnsigned numbers. Now, the sha256 function will be used to generate the hash value 
for the content of the given file again. Following this, the signature from the signature file (file.txt.signature) 
is obtained and converted to a BigUnsigned number. Now the saved hash value (signature from signature file) is encrypted
using the public key stored in the e_n.txt file by using the modexp function by passing in the signature number,
e numnber, and n number. Finially the sha256 hash value generated from the content of the text file (file.txt) is 
compared to the enrypted signature to determine if the file has been changed or not. If the numbers are the same, 
then the file is authentic, if the numbers are different then the file has been modified. The program will output the
results. Finally, the files are closed and the program ends.

To run this part of the program the user will need to type: ./sign v file.txt file.txt.signature
