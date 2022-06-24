#include "Trit.hpp"


const TSet::Trit TSet::operator&(const TSet::Trit& trit1, const TSet::Trit& trit2) {
	if (trit1 == TSet::False || trit2 == TSet::False) {	return TSet::False; }
	else if (trit1 == TSet::Unknown || trit2 == TSet::Unknown) { return TSet::Unknown; }
	else { return TSet::True; }
}

const TSet::Trit TSet::operator|(const TSet::Trit& trit1, const TSet::Trit& trit2) {
	if (trit1 == TSet::True || trit2 == TSet::True) { return TSet::True; }
	else if (trit1 == TSet::Unknown || trit2 == TSet::Unknown) { return TSet::Unknown; }
	else { return TSet::False; }
}

const TSet::Trit TSet::operator!(const TSet::Trit& trit) {
	if (trit == TSet::False) { return TSet::True; }
	else if (trit == TSet::True) { return TSet::False; }
	else { return TSet::Unknown; }
}


const TSet::Trit TSet::TritSet::Reference::operator&(const Reference& trit) {
	TSet::Trit statusBefore = (TSet::Trit)((*trit.trit >> trit.tritsNumber * 2) &  TSetC::LAST_TRIT);
	return *this & statusBefore;
}

const TSet::Trit TSet::TritSet::Reference::operator&(const TSet::Trit& status) {
	TSet::Trit statusBefore = (Trit)((*trit >> tritsNumber * 2) &  TSetC::LAST_TRIT);
	return statusBefore & status;
}

const TSet::Trit TSet::TritSet::Reference::operator|(const Reference& trit) {
	Trit statusBefore = (Trit)((*trit.trit >> trit.tritsNumber * 2) &  TSetC::LAST_TRIT);
	return *this | statusBefore;
}

const TSet::Trit TSet::TritSet::Reference::operator|(const TSet::Trit& status) {
	TSet::Trit statusBefore = (TSet::Trit)((*trit >> tritsNumber * 2) &  TSetC::LAST_TRIT);
	return statusBefore | status;
}

const TSet::Trit TSet::TritSet::Reference::operator!() {
	Trit statusBefore = (Trit)((*trit >> tritsNumber * 2) &  TSetC::LAST_TRIT);
	return !statusBefore;
}

bool TSet::TritSet::Reference::operator==(const TSet::Trit& status) {
	uint32_t shiftLeft = *(this->trit) << (TSetC::FULL_SHIFT - tritsNumber * 2);
	Trit tritStatus = (Trit)(shiftLeft >> TSetC::FULL_SHIFT);
	if (tritStatus == status) { return true; }
	else {	return false; }
}

bool TSet::TritSet::Reference::operator==(const Reference& trit) {
	uint32_t shiftLeft = *(trit.trit) << (TSetC::FULL_SHIFT - trit.tritsNumber * 2);
	Trit tritStatus = (Trit)(shiftLeft >> TSetC::FULL_SHIFT);
	return *this == tritStatus;
}

const bool TSet::TritSet::Reference::operator=(const TSet::Trit& status) {
	if (!isInSize) {
		if (status != TSet::Unknown) {
			uint32_t capacityBefore = (trits->size + TSetC::SizeUintTrits - 1) / TSetC::SizeUintTrits;
			trits->size = bytesNumber * TSetC::SizeUintTrits + tritsNumber + 1;
			if (!isInArea) {
				uint32_t realSize = trits->capacity() / TSetC::SizeUintTrits;
				std::vector<uint32_t> tritsArr = std::vector<uint32_t>(realSize);
				for (uint32_t i = 0; i < capacityBefore; i++) {
					tritsArr[i] = trits->set[i];
				}
				trits->set = tritsArr;
				this->trit = &(trits->set[realSize - 1]);
			}
			else {
				this->trit = &(trits->set[bytesNumber]);
			}
		}
		else {
			return true;
		}
	}
	uint32_t mask = TSetC::UINT_MAX32 - ( TSetC::LAST_TRIT << 2 * tritsNumber);
	*trit = *trit & mask;
	uint32_t trit = status << 2 * tritsNumber;
	*this->trit |= trit;

	return true;
}


const bool TSet::TritSet::Reference::operator=(const Reference& trit) {
	uint32_t uintStatus = (*trit.trit >> trit.tritsNumber * 2) &  TSetC::LAST_TRIT;
	Trit status = (Trit)uintStatus;
	*this = status;
	return true;
}


TSet::TritSet TritsAnd(TSet::TritSet& trits1, TSet::TritSet& trits2, uint32_t capacity) {
	TSet::TritSet newArr(trits1);
	uint32_t end = capacity / TSetC::SizeUintTrits - 1;
	for (uint32_t i = 0; i < end; i++) {
		newArr.getSet()[i] = trits2.getSet()[i] & newArr.getSet()[i];
	}

	uint32_t begin = capacity - TSetC::SizeUintTrits;
	end = trits2.getSize();
	for (uint32_t i = begin; i < end; i++) {
		newArr[i] = newArr[i] & trits2[i];
	}
	return newArr;
}


TSet::TritSet TritsOr(TSet::TritSet& trits1, TSet::TritSet& trits2, uint32_t capacity) {
	TSet::TritSet newArr(trits1);
	uint32_t end = trits2.getSize();
	for (uint32_t i = 0; i < end; i++) {
		newArr[i] = newArr[i] | trits2[i];
	}
	return newArr;
}


TSet::TritSet TSet::TritSet::operator&(TritSet trits) {
	uint32_t first = this->capacity();
	uint32_t second = trits.capacity();
	TritSet newArr;
	if (first > second) {
		newArr = TritsAnd(*this , trits, second);
	}
	else {
		newArr = TritsAnd(trits, *this, first);
	}
	return newArr;
}


TSet::TritSet TSet::TritSet::operator|(TritSet trits) {
	uint32_t first = this->capacity();
	uint32_t second = trits.capacity();
	TritSet newArr;
	if (first > second) {
		newArr = TritsOr(*this , trits, second);
	}
	else {
		newArr = TritsOr(trits, *this, first);
	}
	return newArr;
}


TSet::TritSet TSet::TritSet::operator!() {
	uint32_t capacity = this->capacity();
	TritSet newArr(*this);
	uint32_t end = newArr.getSize();

	for (uint32_t i = 0; i < end; i++) {
		newArr[i] = !newArr[i];
		if (i == 99) {
			int k = 0;
		}
	}
	return newArr;
}


TSet::TritSet::TritSet(const uint32_t& capacityTrits) {
	size = capacityTrits;
	uint32_t realSize = this->capacity() / TSetC::SizeUintTrits;
	std::vector<uint32_t> tritsArr = std::vector<uint32_t>(realSize);
	set = tritsArr;
}


TSet::TritSet::TritSet(const uint32_t& capacityTrits, const Trit& status) {
	size = capacityTrits;
	uint32_t realSize = this->capacity() / TSetC::SizeUintTrits;
	std::vector<uint32_t> tritsArr = std::vector<uint32_t>(realSize);
	set = tritsArr;
	for (int i = 0; i < capacityTrits; i++) {
		(*this)[i] = status;
	}
}


TSet::TritSet::Reference::Reference(const uint32_t& index, TritSet *elem) {
	//trit = &elem->set[index/sizeof(uint32_t)];
	bytesNumber = index / TSetC::SizeUintTrits;
	if (index >= elem->size) {
		isInSize = false;
		if (index >= elem->capacity()) {
			isInArea = false;
		}
		trit = &nullUInt;
	}
	else {
		trit = &elem->set[bytesNumber];
	}

	tritsNumber = index - TSetC::SizeUintTrits * (index / TSetC::SizeUintTrits);
	trits = elem;
}


TSet::TritSet::Reference TSet::TritSet::operator[](const uint32_t& wherePoint) {
	return Reference(wherePoint, this);
}


void TSet::TritSet::trim(const uint32_t& lastIndex) {
	if (lastIndex > 0) {
		uint32_t index = lastIndex + 1;
		if (index <= this->capacity()) {
			uint32_t newSize = (lastIndex - 1) / TSetC::SizeUintTrits;/////
			std::vector<uint32_t> trits = std::vector<uint32_t>(newSize + 1);
			for (uint32_t i = 0; i < newSize; i++) {
				trits[i] = set[i];
			}

			uint32_t num = lastIndex - lastIndex / TSetC::SizeUintTrits * TSetC::SizeUintTrits;
			uint32_t mask = TSetC::UINT_MAX32 >> 32 - (num * 2);
			trits[newSize] = set[newSize] & mask;
			set = trits;
			size = lastIndex;
		}
	}
}

void TSet::TritSet::shrink() {
	this->trim(this->size);
}

uint32_t TSet::TritSet::capacity() {
	uint32_t RealSizeBytes = (size + TSetC::SizeUintTrits - 1) / TSetC::SizeUintTrits;
	return  RealSizeBytes * TSetC::SizeUintTrits;
}

uint32_t TSet::TritSet::cardinality(const Trit value) {
	uint32_t end = this->size;
	uint32_t cardinality = 0;
	
	for (uint32_t i = 0; i < end; i++) {
		if (i == 34) {
			int i3f = 1;
		}
		if ((*this)[i] == value) {
			cardinality++;
		}
	}
	return cardinality;
}
