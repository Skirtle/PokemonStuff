# Generation 3 data structure for Pokemon
#### All information from [Bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_structure_(Generation_III))

### Personality value
#### Used for gender, Unown's letter, Spina's dots, natures, and more
* type: u32

### OT ID
#### Original trainer ID. The number is the XOR encryption key for the data section and is used in Shiny determination and the lottery. First 2 bytes of the Trainer ID are visible to the player, the final 2 bytes are the Secret ID of the trainer who caught it
* type: u32

### Nickname
#### Limited to 10 characters, each byte represents a character in the propietary character set
* type: u8[10]

### Language
#### Language of origin for that Pokemon. Differences noted in the article. Languages can also be found there
* type: u8

###  Misc. flags
#### A byte of 4 different flags.
0. is bad egg - Set to 1 if the egg is a Bad Egg (invalid checksum)
1. Has Species - Set whenever the Pokemon species index is non-zero, used as a sanity check
2. Use Egg Name - Set to ignore nickname and use "EGG" as name, used only for eggs
3. Block Box - Set to disable moving into Pokemon Box
4. Rest of bits are unused and are padding
* type: u8

### OT name
#### Original trainer's name, similar to nickname
* type: u8[7]
* offset: 0x14
* length (bytes): 7

### Markings
#### Markings used in Boxes. Symbol index list found in article
* type: u8

### Checksum
#### Checksum for the 48-byte data section of this structure. 
* type: u16

### ????
#### Unknown, naybe padding?
* type: u16

### Data
#### Data for the Pokemon that is stored in a special and encrypted format
* type: u8[48]

### Status condition
#### See chart for bits
* type: u32 (is this true?)

### Level
#### The Pokemon's level
* type: u8

### Mail ID
#### See article
* type: u8

### Current HP
#### Pokemon's current HP
* type: u16

### Total HP
#### Pokemon's total HP
* type: u16

### Attack
#### Pokemon's attack
* type: u16

### Defense
#### Pokemon's Defense
* type: u16

### Speed
#### Pokemon's Speed
* type: u16

### Spcial Attack
#### Pokemon's Spcial Attack
* type: u16

### Special Defense
#### Pokemon's Special Defense
* type: u16