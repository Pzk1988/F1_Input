#ifndef SPI_H
#define SPI_H

#include "ISpi.hpp"

namespace Driver
{

class Spi: public ISpi
{
public:
	Spi() = default;
	virtual ~Spi() = default;
	void Init();
	uint8_t Write(uint8_t data);
};

} // namespace Driver

#endif // SPI_H
