package main

import (
	"fmt"
	"hash/crc32"
	"log"
)

func CRC32(str string) uint32{
	return crc32.ChecksumIEEE([]byte(str))
}

func main() {
	flag := "cafebe1f"
	key := "HSTCF#" + flag // cafebe1f
	result := CRC32(key)
	log.Println(key)
	log.Println(result)

	key2 := "HSTCF#" + flag + "#" + fmt.Sprintf("%d", result)
	log.Println(key2)
	result2 := CRC32(key2)
	log.Println(result2)

	first := 0
	end := 0xffffffff

	for i := first; i <= end; i++ {
		r := CRC32(fmt.Sprintf("%x", i))
		if r == result {
			log.Println(fmt.Sprintf("FOUND: %x", i))
			break
		}
		if i % 0x10000000 == 0 {
			log.Println(fmt.Sprintf("I: %x", i))
		}
	}
}
