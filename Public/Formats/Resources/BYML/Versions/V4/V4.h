#pragma once

#include <Formats/Resources/BYML/BYML.h>

#include <Formats/Resources/BYML/Versions/V4/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Node.h>

#include <memory>

namespace Formats::Resources::BYML::Versions::V4 {
	class V4 : public Formats::Resources::BYML::BYML {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::Resources::ResourceParsedCallback callback) override;

		virtual std::string ToYAML() override;

		std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::StringTable> mHashKeyTable;
		std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::StringTable> mStringTable;
		std::shared_ptr<Formats::Resources::BYML::Node> mRoot;
	};
}