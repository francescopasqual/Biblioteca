#ifndef DETAILSCREENVISITOR_H
#define DETAILSCREENVISITOR_H

#include "itemvisitor.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "item.h"


class DetailScreenVisitor : public ItemVisitor {
private:
    QWidget* parentWidget;
    QVBoxLayout* mainLayout;

    // Common UI elements
    QLabel* titleLabel;
    QGroupBox* commonDetailsWidget;
    QFormLayout* commonDetailsLayout;

    // Common item values labels
    QLabel* creatorValueLabel;
    QLabel* genreValueLabel;
    QLabel* yearValueLabel;
    QLabel* copiesValueLabel;
    QLabel* loansValueLabel;
    QLabel* availabilityValueLabel;

    // Specific details group (will be populated differently for each item type)
    QGroupBox* specificDetailsWidget;;
    QFormLayout* specificDetailsLayout;

    // Formats section
    QGroupBox* formatsWidget;
    QVBoxLayout* formatsLayout;

    // Action buttons
    QGroupBox* buttonsWidget;
    QHBoxLayout* buttonsLayout;
    QPushButton* exitButton;
    QPushButton* loanButton;
    QPushButton* keepButton;


    // Create and setup the common UI elements
    void setupCommonUI();

    // Update common fields with item data
    void updateCommonFields(Item* item);


public:

    DetailScreenVisitor(QWidget* parent);
    ~DetailScreenVisitor();

    void visit(Libro* libro) override;
    void visit(Film* film) override;
    void visit(Vinile* vinile) override;

    // Getters for buttons to connect signals
    QPushButton* getExitButton() const { return exitButton; }
    QPushButton* getLoanButton() const { return loanButton; }
    QPushButton* getKeepButton() const { return keepButton; }
};

#endif // DETAILSCREENVISITOR_H
