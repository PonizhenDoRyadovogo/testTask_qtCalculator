#ifndef IVIEW_H
#define IVIEW_H

#include <QString>

class IView {
public:
    virtual ~IView() = default;

    virtual void setDisplayText(const QString& text) = 0;
    virtual QString getDisplayText() const = 0;
    virtual void showError(const QString& errorMessage) = 0;
    virtual void setExpressionText(const QString& text) = 0;
    virtual void setEqualsIndicatorVisible(bool visible) = 0;
    virtual QString getExpressionText() const = 0;
};

#endif // IVIEW_H
