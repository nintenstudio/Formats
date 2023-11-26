#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/Versions/V7/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Double.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/FileData.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Float.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Int64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Null.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/String.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>

#include <memory>

namespace Formats::Resources::BYML::Versions::V7 {
	std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node> Node::Factory(Formats::Resources::BYML::Versions::V7::V7* parentBYML, YAML::Node& node) {
		std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node> res;

		if (node.IsSequence()) {
			res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(parentBYML);
		}
		else if (node.IsMap()) {
			if (node.Tag() == "!plainhash")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(parentBYML);
			else if (node.Tag() == "!valuehash")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(parentBYML);
			else
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(parentBYML);
		}
		else if (node.IsScalar()) {
			if (node.Tag() == "!uint32")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt>(parentBYML);
			else if (node.Tag() == "!sint32")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int>(parentBYML);
			else if (node.Tag() == "!uint64")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt64>(parentBYML);
			else if (node.Tag() == "!sint64")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int64>(parentBYML);
			else if (node.Tag() == "!float32")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Float>(parentBYML);
			else if (node.Tag() == "!float64")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Double>(parentBYML);
			else if (node.Tag() == "!bool")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Bool>(parentBYML);
			else if (node.Tag() == "!binarydata")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData>(parentBYML);
			else if (node.Tag() == "!filedata")
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::FileData>(parentBYML);
			else
				res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>(parentBYML);
		}
		else if (node.IsNull()) {
			res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Null>(parentBYML);
		}
		else {
			res = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>(parentBYML);
		}

		return res;
	}
}