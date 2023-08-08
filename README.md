# Linux-kernel-module
This is a char module that simulates a bank where we can create accounts or delete accounts. It should also be possible to withdraw, deposit and transfer money in this bank.

Transfer 12 currency units from account 17 to account 22 :

e,17,22,12

Deposit 3 currency units to account 47:

v,-,47,3

Withdrawal of 44 currency units from the account 97:

b,97,-,44
# Requirements
linux-headers

`sudo apt install linux-headers-$(uname -r)`
