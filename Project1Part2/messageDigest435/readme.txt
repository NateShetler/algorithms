Nathaniel Shetler
ID: 4015423
Class: Algorithms

Project1Part2:

During this part of the project, the program will allow you to sign the document with a digital signature
or verify a signed document to see if it is valid or if it has been modified. 

Signing a file:
To accomplish this, the sha256 function will be used to generate a hash value for the content of a given 
file (file.txt). After the sha256 value is obtained, it is converted to a BigUnsigned number and then decrypt 
it using the private key stored in d_n.txt. The new digital signature that is made is then stored into a 
signature file named file.txt.signature.  

Verifying a file:
