#ifndef JFS_ITEMFILE_H
#define JFS_ITEMFILE_H
#include <map>
#include "item.h"
#include "weapon.h"
namespace labb3
{
	class ItemFile{
		public:
			static std::map<std::string, Item*>& getItems();
			~ItemFile();
	};
}
#endif
