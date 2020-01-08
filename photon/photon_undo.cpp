#include "photon_undo.hpp"


PhotonUndo::PhotonUndo(rs::Image &&img, LabelImage *labelPtr, UndoPreview *undoPrevPtr)
    : m_undo(std::move(img)),
      m_imageLoaded(true),
      m_labelPtr(labelPtr),
      m_undoPreviewPtr(undoPrevPtr)
{
    this->updateLabel();
}

PhotonUndo::PhotonUndo() : PhotonUndo(rs::Image(), nullptr, nullptr) {
    m_imageLoaded = false;
}

const rs::Image &PhotonUndo::origin() const { return m_undo.origin(); }

const rs::Image &PhotonUndo::current() const { return m_undo.current(); }

std::pair<bool, bool> PhotonUndo::undo() {
    if (!m_imageLoaded)
        return {false, false};

    auto retval = m_undo.undo();
    this->updateFriendComponents();
    return retval;
}

std::pair<bool, bool> PhotonUndo::redo() {

    if (!m_imageLoaded)
        return {false, false};

    auto retval = m_undo.redo();
    this->updateFriendComponents();
    return retval;
}

std::vector<std::shared_ptr<const rs::Transform> > PhotonUndo::previousActions() const {
    if (!m_imageLoaded)
        return {};

    return m_undo.previousActions();
}

std::vector<std::shared_ptr<const rs::Transform> > PhotonUndo::nextActions() const {
    if (!m_imageLoaded)
        return {};

    return m_undo.nextActions();
}

unsigned PhotonUndo::numOfPreviousActions() const {
    if (!m_imageLoaded)
        return 0;
    return m_undo.numOfPreviousActions();
}

unsigned PhotonUndo::numOfNextActions() const {
    if (!m_imageLoaded)
        return 0;
    return m_undo.numOfNextActions();
}

void PhotonUndo::updateFriendComponents() {
    if (!m_imageLoaded)
        return;

    this->updateLabel();
    this->updateUndoPreview();
}

void PhotonUndo::updateLabel() {
    if (!m_imageLoaded)
        return;

    if (m_labelPtr == nullptr)
        return;

    const rs::Image &imgRef = this->current();
    QImage qimg = QImage(imgRef.data(), imgRef.width(), imgRef.height(), imgRef.step(), QImage::Format_BGR888);
    m_labelPtr->setPixmap(QPixmap::fromImage(std::move(qimg)));
}

void PhotonUndo::updateUndoPreview() {

    if (!m_imageLoaded)
        return;

    if (m_undoPreviewPtr == nullptr)
        return;

    this->m_undoPreviewPtr->updatePreview(
                m_undo.previousActions(),
                m_undo.nextActions()
                );
}
