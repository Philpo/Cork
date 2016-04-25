#pragma once
#include "IPass.h"
#include "RapidXML\rapidxml.hpp"
#include "MessageHandler.h"
#include "Message.h"
#include "ServiceLocator.h"
#include "GraphicsTypeDefs.h"
#include "Utils.h"
#include <map>

using namespace std;
using namespace rapidxml;

class DirectX11Pass : public IPass {
public:
  DirectX11Pass(xml_node<>* passNode);
  ~DirectX11Pass() {}

  int getNumRenderTargets() const override { return renderTargets.size(); }
  const std::vector<string>& getRenderTargets() const override { return renderTargets; }
  const string& getDepthBuffer() const override { return depthBuffer; }
  const string& getViewPort() const override { return viewport; }
  void* const getRenderTargetBindTargets() const override { return (void*) &renderTargetBindTargets; }
  void* const getDepthBufferBindTargets() const override { return (void*) &depthBufferBindTargets; }

  void setRenderTargets(const vector<string>& renderTargets) override { this->renderTargets = renderTargets; }
  void setDepthBuffer(string& depthBuffer) override { this->depthBuffer = depthBuffer; }
  void setViewport(string& viewport) override { this->viewport = viewport; }
  void setRenderTargetBindTargets(void* const bindTargets) override { this->renderTargetBindTargets = *(map<int, string>*) bindTargets; }
  void setDepthBufferBindTargets(void* const bindTargets) override { this->depthBufferBindTargets = *(map<int, string>*) bindTargets; }
private:
  int height, width;
  string depthBuffer, viewport;
  vector<string> renderTargets;
  map<int, string> renderTargetBindTargets, depthBufferBindTargets;

  void readAndCreateRenderTarget(xml_node<>* renderTargetNode);
  void readAndCreateDepthBuffer(xml_node<>* depthBufferNode);
  void readAndCreateViewport(xml_node<>* viewportNode);
  pair<int, string> readBindTarget(xml_node<>* bindNode);
};