# Generation 3 data stucture for Pokemon data
#### All information from [Bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_substructures_(Generation_III))

## Stored as 4 distinct substuctures of 12 bytes each

### Growth section
* Species: 2 bytes
* Item held: 2 bytes
* Experience: 4 bytes
* Friendship: 1 byte
* Unused: 2 bytes

### Attacks section
* Move 1: 2 bytes
* Move 2: 2 bytes
* Move 3: 2 bytes
* Move 4: 2 bytes
* PP 1: 1 byte
* PP 2: 1 byte
* PP 3: 1 byte
* PP 4: 1 byte

### EVs and Condition section
* HP EV: 1 byte
* Attack EV: 1 byte
* Defense EV: 1 byte
* Speed EV: 1 byte
* Special attack EV:1 byte
* Special defense EV: 1 byte
* Coolness: 1 byte
* Beauty: 1 byte
* Cuteness: 1 byte
* Smartness: 1 byte
* Toughness: 1 byte
* Feel: 1 byte

### Misc. section
* Pokeruse status: 1 byte
* Met location: 1 byte
* Origins info: 2 bytes
* IV's, Egg, and Ability: 4 bytes
* Ribbons and Obedience: 4 bytes

## Substructure order
Order of the substructures is dependent on the personality value of the Pokemon, mod 24
00. GAEM	06. AGEM	12. EGAM	18. MGAE
01. GAME	07. AGME	13. EGMA	19. MGEA
02. GEAM	08. AEGM	14. EAGM	20. MAGE
03. GEMA	09. AEMG	15. EAMG	21. MAEG
04. GMAE	10. AMGE	16. EMGA	22. MEGA
05. GMEA	11. AMEG	17. EMAG	23. MEAG

# Encyrption
Decrypting the data involves 2 steps, decrypting it and then validating it
### Obtaining the key
The entire OT ID must be XOR'd with the personality value of the entry.
### Decrypting
Use this key to decrypt the data by XORing it, 4 bytes at a time.
### Validating the checksum 
The entirety of the 4 unencrypted data substructures must be summed into a 16-bit value