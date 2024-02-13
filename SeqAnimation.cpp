#include "SeqAnimation.h"

SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat){}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip) {
	TextureManager::GetInstance()->Draw(m_CurrSeq.TextureIDs[m_CurrFrame], x, y, m_CurrSeq.Width, m_CurrSeq.Height, xScale, yScale, 1.0, flip);
}

void SeqAnimation::Update(float dt) {
	if (m_Repeat || !m_IsEnded) {
		m_IsEnded = false;
		m_CurrFrame = (SDL_GetTicks64()/m_CurrSeq.Speed) % m_CurrSeq.FrameCount;
	}

	if (!m_Repeat && m_CurrFrame == (m_CurrSeq.FrameCount - 1)) {
		m_IsEnded = true;
		m_CurrFrame = (m_CurrSeq.FrameCount - 1);
	}
}

void SeqAnimation::SetCurrentSeq(std::string seqID) {
	if (m_SeqMap.count(seqID) > 0)
		m_CurrSeq = m_SeqMap[seqID];
	else
		std::cout << "Animation sequence " << seqID << " not found" << std::endl;
}

void SeqAnimation::Parse(std::string source){
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cout << "Failed to load animation file " << source << std::endl;
		return;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("sequence")) {
			Sequence seq;
			std::string seqID = e->Attribute("id");
			e->Attribute("speed", &seq.Speed);
			e->Attribute("width", &seq.Width);
			e->Attribute("height", &seq.Height);
			e->Attribute("frameCount", &seq.FrameCount);
			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement()) {
				seq.TextureIDs.push_back(frame->Attribute("textureID"));
			}
			m_SeqMap[seqID] = seq;
		}
	}
}