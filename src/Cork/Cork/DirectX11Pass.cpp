#include "DirectX11Pass.h"

DirectX11Pass::DirectX11Pass(xml_node<>* passNode) : depthBuffer(""), viewport("") {
  if (passNode) {
    try {
      height = convertStringToNumber<int>(passNode->first_attribute("height")->value());
      width = convertStringToNumber<int>(passNode->first_attribute("width")->value());

      if (passNode->first_node("render_targets")) {
        for (xml_node<>* renderTargetNode = passNode->first_node("render_targets")->first_node(); renderTargetNode; renderTargetNode = renderTargetNode->next_sibling()) {
          readAndCreateRenderTarget(renderTargetNode);
        }
      }
      else {
        renderTargets = { "null" };
      }

      if (passNode->first_node("depth_buffer")) {
        readAndCreateDepthBuffer(passNode->first_node("depth_buffer"));
      }

      readAndCreateViewport(passNode->first_node("viewport"));

      if (passNode->first_node("render_target_binds")) {
        for (xml_node<>* bindNode = passNode->first_node("render_target_binds")->first_node(); bindNode; bindNode = bindNode->next_sibling()) {
          renderTargetBindTargets.insert(readBindTarget(bindNode));
        }
      }

      if (passNode->first_node("depth_buffer_binds")) {
        for (xml_node<>* bindNode = passNode->first_node("depth_buffer_binds")->first_node(); bindNode; bindNode = bindNode->next_sibling()) {
          depthBufferBindTargets.insert(readBindTarget(bindNode));
        }
      }
    }
    catch (exception&) {
      throw;
    }
  }
}

void DirectX11Pass::readAndCreateRenderTarget(xml_node<>* renderTargetNode) {
  CreateInfo info;
  
  try {
    info.height = height;
    info.width = width;
    info.createTextureView = convertStringToBool(renderTargetNode->first_attribute("create_texture_view")->value());
    info.renderToBackBuffer = convertStringToBool(renderTargetNode->first_attribute("render_to_back_buffer")->value());
    info.id = renderTargetNode->first_attribute("id")->value();
    info.format = convertStringToNumber<int>(renderTargetNode->first_attribute("format")->value());
    info.textureViewFormat = convertStringToNumber<int>(renderTargetNode->first_attribute("texture_view_format")->value());

    MessageHandler::forwardMessage(Message(CREATE_RENDER_TARGET_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    renderTargets.push_back(info.id);
  }
  catch (exception&) {
    throw;
  }
}

void DirectX11Pass::readAndCreateDepthBuffer(xml_node<>* depthBufferNode) {
  CreateInfo info;

  try {
    info.height = height;
    info.width = width;
    info.createTextureView = convertStringToBool(depthBufferNode->first_attribute("create_texture_view")->value());
    info.id = depthBufferNode->first_attribute("id")->value();
    info.format = convertStringToNumber<int>(depthBufferNode->first_attribute("format")->value());
    info.depthBufferFormat = convertStringToNumber<int>(depthBufferNode->first_attribute("depth_buffer_format")->value());
    info.textureViewFormat = convertStringToNumber<int>(depthBufferNode->first_attribute("texture_view_format")->value());

    MessageHandler::forwardMessage(Message(CREATE_DEPTH_BUFFER_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    depthBuffer = info.id;
  }
  catch (exception&) {
    throw;
  }
}

void DirectX11Pass::readAndCreateViewport(xml_node<>* viewportNode) {
  CreateInfo info;

  try {
    info.height = height;
    info.width = width;
    info.id = viewportNode->first_attribute("id")->value();
    MessageHandler::forwardMessage(Message(CREATE_VIEWPORT_MESSAGE, &info, ServiceLocator::getMessageHandler(GRAPHICS_COMPONENT)));
    viewport = info.id;
  }
  catch (exception&) {
    throw;
  }
}

pair<int, string> DirectX11Pass::readBindTarget(xml_node<>* bindNode) {
  try {
    int shaderSlot = convertStringToNumber<int>(bindNode->first_attribute("shader_slot")->value());
    string target = bindNode->first_attribute("target")->value();

    return pair<int, string>(shaderSlot, target);
  }
  catch (exception&) {
    throw;
  }
}