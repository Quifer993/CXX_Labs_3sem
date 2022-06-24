#pragma once
#include <vector>
#include <stdint.h>
#include "TConst.hpp"

namespace TSet { // добавить в константы
	enum Trit { Unknown, True, False };

	const Trit operator&(const Trit& trit1, const Trit& trit2);
	const Trit operator|(const Trit& trit1, const Trit& trit2);
	const Trit operator!(const Trit& trit);

	class TritSet
	{
	private:
		std::vector < uint32_t> set;
		uint32_t size;

		class Reference {
		private:
			uint32_t* trit;
			uint32_t nullUInt = 0;
			uint32_t tritsNumber;
			uint32_t bytesNumber;
			TritSet* trits;
			bool isInArea = true;
			bool isInSize = true;
		public:

			Reference() = default;
			~Reference() = default;

			Reference(const uint32_t& index, TritSet* elem);

			const Trit operator&(const Reference& trit);

			const Trit operator&(const Trit& status);

			const Trit operator|(const Reference& trit);

			const Trit operator|(const Trit& status);

			const Trit operator!();

			bool operator==(const Trit& status);

			bool operator==(const Reference& trit);

			const bool operator=(const Trit& status);

			const bool operator=(const Reference& trit);

		};
	public:

		TritSet() = default;
		~TritSet() = default;

		TritSet(const uint32_t& capacityTrits);
		TritSet(const uint32_t& capacityTrits, const Trit& status);

		uint32_t getSize() { return size; }

		uint32_t capacity();

		std::vector < uint32_t>& getSet() { return set; }

		Reference operator[](const uint32_t& wherePoint);

		TritSet operator&(TritSet trits);

		TritSet operator|(TritSet trits);

		TritSet operator!();

		void trim(const uint32_t& lastIndex);

		uint32_t cardinality(const Trit value);

		void shrink();
	};
}